require "uri"
require "rubygems/installer"
require "rubygems/spec_fetcher"
require "rubygems/format"
require "digest/sha1"
require "open3"

module Bundler
  module Source
    # TODO: Refactor this class
    class Rubygems
      attr_reader :remotes

      def initialize(options = {})
        @options = options
        @remotes = (options["remotes"] || []).map { |r| normalize_uri(r) }
        @allow_remote = false
        @allow_cached = false
        # Hardcode the paths for now
        @caches = [ Bundler.app_cache ] + Gem.path.map { |p| File.expand_path("#{p}/cache") }
        @spec_fetch_map = {}
      end

      def remote!
        @allow_remote = true
      end

      def cached!
        @allow_cached = true
      end

      def hash
        Rubygems.hash
      end

      def eql?(o)
        Rubygems === o
      end

      alias == eql?

      # Not really needed, but it seems good to implement this method for interface
      # consistency. Source name is mostly used to identify Path & Git sources
      def name
        ":gems"
      end

      def options
        { "remotes" => @remotes.map { |r| r.to_s } }
      end

      def self.from_lock(options)
        s = new(options)
        Array(options["remote"]).each { |r| s.add_remote(r) }
        s
      end

      def to_lock
        out = "GEM\n"
        out << remotes.map {|r| "  remote: #{r}\n" }.join
        out << "  specs:\n"
      end

      def to_s
        remotes = self.remotes.map { |r| r.to_s }.join(', ')
        "rubygems repository #{remotes}"
      end

      def specs
        @specs ||= fetch_specs
      end

      def fetch(spec)
        spec, uri = @spec_fetch_map[spec.full_name]
        if spec
          path = download_gem_from_uri(spec, uri)
          s = Gem::Format.from_file_by_path(path).spec
          spec.__swap__(s)
        end
      end

      def install(spec)
        path = cached_gem(spec)

        if installed_specs[spec].any?
          Bundler.ui.info "Using #{spec.name} (#{spec.version}) "
          return
        end

        Bundler.ui.info "Installing #{spec.name} (#{spec.version}) "

        install_path = Bundler.requires_sudo? ? Bundler.tmp : Gem.dir
        options = { :install_dir         => install_path,
                    :ignore_dependencies => true,
                    :wrappers            => true,
                    :env_shebang         => true }
        options.merge!(:bin_dir => "#{install_path}/bin") unless spec.executables.nil? || spec.executables.empty?

        installer = Gem::Installer.new path, options
        installer.install

        # SUDO HAX
        if Bundler.requires_sudo?
          sudo "mkdir -p #{Gem.dir}/gems #{Gem.dir}/specifications"
          sudo "cp -R #{Bundler.tmp}/gems/#{spec.full_name} #{Gem.dir}/gems/"
          sudo "cp -R #{Bundler.tmp}/specifications/#{spec.full_name}.gemspec #{Gem.dir}/specifications/"
          spec.executables.each do |exe|
            sudo "mkdir -p #{Gem.bindir}"
            sudo "cp -R #{Bundler.tmp}/bin/#{exe} #{Gem.bindir}"
          end
        end

        spec.loaded_from = "#{Gem.dir}/specifications/#{spec.full_name}.gemspec"
      end

      def sudo(str)
        Bundler.sudo(str)
      end

      def cache(spec)
        cached_path = cached_gem(spec)
        raise GemNotFound, "Missing gem file '#{spec.full_name}.gem'." unless cached_path
        return if File.dirname(cached_path) == Bundler.app_cache.to_s
        Bundler.ui.info "  * #{File.basename(cached_path)}"
        FileUtils.cp(cached_path, Bundler.app_cache)
      end

      def add_remote(source)
        @remotes << normalize_uri(source)
      end

      def merge_remotes(source)
        @remotes = []
        source.remotes.each do |r|
          add_remote r.to_s
        end
      end

    private

      def cached_gem(spec)
        possibilities = @caches.map { |p| "#{p}/#{spec.full_name}.gem" }
        possibilities.find { |p| File.exist?(p) }
      end

      def normalize_uri(uri)
        uri = uri.to_s
        uri = "#{uri}/" unless uri =~ %r'/$'
        uri = URI(uri)
        raise ArgumentError, "The source must be an absolute URI" unless uri.absolute?
        uri
      end

      def fetch_specs
        Index.build do |idx|
          idx.use installed_specs
          idx.use cached_specs if @allow_cached || @allow_remote
          idx.use remote_specs if @allow_remote
        end
      end

      def installed_specs
        @installed_specs ||= begin
          idx = Index.new
          have_bundler = false
          Gem::SourceIndex.from_installed_gems.to_a.reverse.each do |dont_use_this_var, spec|
            next if spec.name == 'bundler' && spec.version.to_s != VERSION
            have_bundler = true if spec.name == 'bundler'
            spec.source = self
            idx << spec
          end

          # Always have bundler locally
          unless have_bundler
           # We're running bundler directly from the source
           # so, let's create a fake gemspec for it (it's a path)
           # gemspec
           bundler = Gem::Specification.new do |s|
             s.name     = 'bundler'
             s.version  = VERSION
             s.platform = Gem::Platform::RUBY
             s.source   = self
             # TODO: Remove this
             s.loaded_from = 'w0t'
           end
           idx << bundler
          end
          idx
        end
      end

      def cached_specs
        @cached_specs ||= begin
          idx = Index.new
          @caches.each do |path|
            Dir["#{path}/*.gem"].each do |gemfile|
              next if name == 'bundler'
              s = Gem::Format.from_file_by_path(gemfile).spec
              s.source = self
              idx << s
            end
          end
          idx
        end
      end

      def remote_specs
        @remote_specs ||= begin
          idx     = Index.new
          old     = Gem.sources

          remotes.each do |uri|
            Bundler.ui.info "Fetching source index for #{uri}"
            Gem.sources = ["#{uri}"]
            fetch_all_remote_specs do |n,v|
              v.each do |name, version, platform|
                next if name == 'bundler'
                spec = RemoteSpecification.new(name, version, platform, uri)
                spec.source = self
                @spec_fetch_map[spec.full_name] = [spec, uri]
                idx << spec
              end
            end
          end
          idx
        ensure
          Gem.sources = old
        end
      end

      def fetch_all_remote_specs(&blk)
        begin
          # Fetch all specs, minus prerelease specs
          Gem::SpecFetcher.new.list(true, false).each(&blk)
          # Then fetch the prerelease specs
          begin
            Gem::SpecFetcher.new.list(false, true).each(&blk)
          rescue Gem::RemoteFetcher::FetchError
            Bundler.ui.warn "Could not fetch prerelease specs from #{self}"
          end
        rescue Gem::RemoteFetcher::FetchError
          Bundler.ui.warn "Could not reach #{self}"
        end
      end

      def download_gem_from_uri(spec, uri)
        spec.fetch_platform

        download_path = Bundler.requires_sudo? ? Bundler.tmp : Gem.dir
        gem_path = "#{Gem.dir}/cache/#{spec.full_name}.gem"

        FileUtils.mkdir_p("#{download_path}/cache")
        Gem::RemoteFetcher.fetcher.download(spec, uri, download_path)

        if Bundler.requires_sudo?
          sudo "mkdir -p #{Gem.dir}/cache"
          sudo "mv #{Bundler.tmp}/cache/#{spec.full_name}.gem #{gem_path}"
        end

        gem_path
      end
    end

    class Path
      attr_reader :path, :options
      # Kind of a hack, but needed for the lock file parser
      attr_writer   :name
      attr_accessor :version

      DEFAULT_GLOB = "{,*/}*.gemspec"

      def initialize(options)
        @options = options
        @glob = options["glob"] || DEFAULT_GLOB

        @allow_cached = false
        @allow_remote = false

        if options["path"]
          @path = Pathname.new(options["path"]).expand_path(Bundler.root)
        end

        @name = options["name"]
        @version = options["version"]
      end

      def remote!
        @allow_remote = true
      end

      def cached!
        @allow_cached = true
      end

      def self.from_lock(options)
        new(options.merge("path" => options.delete("remote")))
      end

      def to_lock
        out = "PATH\n"
        out << "  remote: #{relative_path}\n"
        out << "  glob: #{@glob}\n" unless @glob == DEFAULT_GLOB
        out << "  specs:\n"
      end

      def to_s
        "source at #{@path}"
      end

      def hash
        self.class.hash
      end

      def eql?(o)
        o.instance_of?(Path) &&
        path == o.path &&
        name == o.name &&
        version == o.version
      end

      alias == eql?

      def name
        File.basename(@path.to_s)
      end

      def load_spec_files
        index = Index.new

        if File.directory?(path)
          Dir["#{path}/#{@glob}"].each do |file|
            spec = Bundler.load_gemspec(file)
            if spec
              spec.loaded_from = file.to_s
              spec.source = self
              index << spec
            end
          end

          if index.empty? && @name && @version
            index << Gem::Specification.new do |s|
              s.name     = @name
              s.source   = self
              s.version  = Gem::Version.new(@version)
              s.platform = Gem::Platform::RUBY
              s.summary  = "Fake gemspec for #{@name}"
              s.relative_loaded_from = "#{@name}.gemspec"
              if path.join("bin").exist?
                binaries = path.join("bin").children.map{|c| c.basename.to_s }
                s.executables = binaries
              end
            end
          end
        else
          raise PathError, "The path `#{path}` does not exist."
        end

        index
      end

      def local_specs
        @local_specs ||= load_spec_files
      end

      class Installer < Gem::Installer
        def initialize(spec, options = {})
          @spec              = spec
          @bin_dir           = Bundler.requires_sudo? ? "#{Bundler.tmp}/bin" : "#{Gem.dir}/bin"
          @gem_dir           = spec.full_gem_path
          @wrappers          = options[:wrappers] || true
          @env_shebang       = options[:env_shebang] || true
          @format_executable = options[:format_executable] || false
        end

        def generate_bin
          return if spec.executables.nil? || spec.executables.empty?

          if Bundler.requires_sudo?
            FileUtils.mkdir_p("#{Bundler.tmp}/bin") unless File.exist?("#{Bundler.tmp}/bin")
          end
          super
          if Bundler.requires_sudo?
            Bundler.mkdir_p "#{Gem.dir}/bin"
            spec.executables.each do |exe|
              Bundler.sudo "cp -R #{Bundler.tmp}/bin/#{exe} #{Gem.dir}/bin/"
            end
          end
        end
      end

      def install(spec)
        Bundler.ui.info "Using #{spec.name} (#{spec.version}) from #{to_s} "
        # Let's be honest, when we're working from a path, we can't
        # really expect native extensions to work because the whole point
        # is to just be able to modify what's in that path and go. So, let's
        # not put ourselves through the pain of actually trying to generate
        # the full gem.
        Installer.new(spec).generate_bin
      end

      alias specs local_specs

      def cache(spec)
        unless path.to_s.index(Bundler.root.to_s) == 0
          Bundler.ui.warn "  * #{spec.name} at `#{path}` will not be cached."
        end
      end

    private

      def relative_path
        if path.to_s.include?(Bundler.root.to_s)
          return path.relative_path_from(Bundler.root)
        end

        path
      end

      def generate_bin(spec)
        gem_dir  = Pathname.new(spec.full_gem_path)

        # Some gem authors put absolute paths in their gemspec
        # and we have to save them from themselves
        spec.files = spec.files.map do |p|
          next if File.directory?(p)
          begin
            Pathname.new(p).relative_path_from(gem_dir).to_s
          rescue ArgumentError
            p
          end
        end.compact

        gem_file = Dir.chdir(gem_dir){ Gem::Builder.new(spec).build }

        installer = Installer.new(spec, :env_shebang => false)
        installer.build_extensions
        installer.generate_bin
      rescue Gem::InvalidSpecificationException => e
        Bundler.ui.warn "\n#{spec.name} at #{spec.full_gem_path} did not have a valid gemspec.\n" \
                        "This prevents bundler from installing bins or native extensions, but " \
                        "that may not affect its functionality."

        if !spec.extensions.empty? && !spec.email.empty?
          Bundler.ui.warn "If you need to use this package without installing it from a gem " \
                          "repository, please contact #{spec.email} and ask them " \
                          "to modify their .gemspec so it can work with `gem build`."
        end

        Bundler.ui.warn "The validation message from Rubygems was:\n  #{e.message}"
      ensure
        Dir.chdir(gem_dir){ FileUtils.rm_rf(gem_file) if gem_file && File.exist?(gem_file) }
      end

    end

    class Git < Path
      attr_reader :uri, :ref, :options, :submodules

      def initialize(options)
        super
        @uri        = options["uri"]
        @ref        = options["ref"] || options["branch"] || options["tag"] || 'master'
        @revision   = options["revision"]
        @submodules = options["submodules"]
        @update     = false
      end

      def self.from_lock(options)
        new(options.merge("uri" => options.delete("remote")))
      end

      def to_lock
        out = "GIT\n"
        out << "  remote: #{@uri}\n"
        out << "  revision: #{revision}\n"
        %w(ref branch tag submodules).each do |opt|
          out << "  #{opt}: #{options[opt]}\n" if options[opt]
        end
        out << "  glob: #{@glob}\n" unless @glob == DEFAULT_GLOB
        out << "  specs:\n"
      end

      def eql?(o)
        Git === o            &&
        uri == o.uri         &&
        ref == o.ref         &&
        name == o.name       &&
        version == o.version &&
        submodules == o.submodules
      end

      alias == eql?

      def to_s
        ref = @options["ref"] ? shortref_for_display(@options["ref"]) : @ref
        "#{@uri} (at #{ref})"
      end

      def name
        File.basename(@uri, '.git')
      end

      def path
        @install_path ||= begin
          git_scope = "#{base_name}-#{shortref_for_path(revision)}"

          if Bundler.requires_sudo?
            Bundler.user_bundle_path.join(Bundler.ruby_scope).join(git_scope)
          else
            Bundler.install_path.join(git_scope)
          end
        end
      end

      def unlock!
        @revision = nil
      end

      # TODO: actually cache git specs
      def specs
        if allow_git_ops? && !@update
        # Start by making sure the git cache is up to date
          cache
          checkout
          @update = true
        end
        local_specs
      end

      def install(spec)
        Bundler.ui.info "Using #{spec.name} (#{spec.version}) from #{to_s} "

        unless @installed
          Bundler.ui.debug "  * Checking out revision: #{ref}"
          checkout if allow_git_ops?
          @installed = true
        end
        generate_bin(spec)
      end

      def load_spec_files
        super
      rescue PathError, GitError
        raise GitError, "#{to_s} is not checked out. Please run `bundle install`"
      end

    private

      def git(command)
        if allow_git_ops?
          out = %x{git #{command}}

          if $? != 0
            raise GitError, "An error has occurred in git when running `git #{command}. Cannot complete bundling."
          end
          out
        else
          raise GitError, "Bundler is trying to run a `git #{command}` at runtime. You probably need to run `bundle install`. However, " \
                          "this error message could probably be more useful. Please submit a ticket at http://github.com/carlhuda/bundler/issues " \
                          "with steps to reproduce as well as the following\n\nCALLER: #{caller.join("\n")}"
        end
      end

      def base_name
        File.basename(uri.sub(%r{^(\w+://)?([^/:]+:)},''), ".git")
      end

      def shortref_for_display(ref)
        ref[0..6]
      end

      def shortref_for_path(ref)
        ref[0..11]
      end

      def uri_hash
        if uri =~ %r{^\w+://(\w+@)?}
          # Downcase the domain component of the URI
          # and strip off a trailing slash, if one is present
          input = URI.parse(uri).normalize.to_s.sub(%r{/$},'')
        else
          # If there is no URI scheme, assume it is an ssh/git URI
          input = uri
        end
        Digest::SHA1.hexdigest(input)
      end

      def cache_path
        @cache_path ||= begin
          git_scope = "#{base_name}-#{uri_hash}"

          if Bundler.requires_sudo?
            Bundler.user_bundle_path.join("cache/git", git_scope)
          else
            Bundler.cache.join("git", git_scope)
          end
        end
      end

      def cache
        if cached?
          return if has_revision_cached?
          Bundler.ui.info "Updating #{uri}"
          in_cache { git %|fetch --force --quiet "#{uri}" refs/heads/*:refs/heads/*| }
        else
          Bundler.ui.info "Fetching #{uri}"
          FileUtils.mkdir_p(cache_path.dirname)
          git %|clone "#{uri}" "#{cache_path}" --bare --no-hardlinks|
        end
      end

      def checkout
        unless File.exist?(path.join(".git"))
          FileUtils.mkdir_p(path.dirname)
          git %|clone --no-checkout "#{cache_path}" "#{path}"|
        end
        Dir.chdir(path) do
          git %|fetch --force --quiet "#{cache_path}"|
          git "reset --hard #{revision}"

          if @submodules
            git "submodule init"
            git "submodule update"
          end
        end
      end

      def has_revision_cached?
        return unless @revision
        in_cache { git %|cat-file -e #{@revision}| }
        true
      rescue GitError
        false
      end

      def allow_git_ops?
        @allow_remote || @allow_cached
      end

      def revision
        @revision ||= begin
          if allow_git_ops?
            in_cache { git("rev-parse #{ref}").strip }
          else
            raise GitError, "The git source #{uri} is not yet checked out. Please run `bundle install` before trying to start your application"
          end
        end
      end

      def cached?
        cache_path.exist?
      end

      def in_cache(&blk)
        cache unless cached?
        Dir.chdir(cache_path, &blk)
      end
    end
  end
end
