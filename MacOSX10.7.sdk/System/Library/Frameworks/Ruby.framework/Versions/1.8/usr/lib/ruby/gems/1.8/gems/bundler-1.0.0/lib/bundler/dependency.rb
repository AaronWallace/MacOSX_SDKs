require 'rubygems/dependency'
require 'bundler/shared_helpers'
require 'bundler/rubygems_ext'

module Bundler
  class Dependency < Gem::Dependency
    attr_reader :autorequire
    attr_reader :groups
    attr_reader :platforms

    PLATFORM_MAP = {
      :ruby    => Gem::Platform::RUBY,
      :ruby_18 => Gem::Platform::RUBY,
      :ruby_19 => Gem::Platform::RUBY,
      :mri     => Gem::Platform::RUBY,
      :mri_18  => Gem::Platform::RUBY,
      :mri_19  => Gem::Platform::RUBY,
      :jruby   => Gem::Platform::JAVA,
      :mswin   => Gem::Platform::MSWIN
    }.freeze

    def initialize(name, version, options = {}, &blk)
      super(name, version)

      @autorequire = nil
      @groups      = Array(options["group"] || :default).map { |g| g.to_sym }
      @source      = options["source"]
      @platforms   = Array(options["platforms"])
      @env         = options["env"]

      if options.key?('require')
        @autorequire = Array(options['require'] || [])
      end
    end

    def gem_platforms(valid_platforms)
      return valid_platforms if @platforms.empty?

      platforms = []
      @platforms.each do |p|
        platform = PLATFORM_MAP[p]
        next unless valid_platforms.include?(platform)
        platforms |= [platform]
      end
      platforms
    end

    def should_include?
      current_env? && current_platform?
    end

    def current_env?
      return true unless @env
      if Hash === @env
        @env.all? do |key, val|
          ENV[key.to_s] && (String === val ? ENV[key.to_s] == val : ENV[key.to_s] =~ val)
        end
      else
        ENV[@env.to_s]
      end
    end

    def current_platform?
      return true if @platforms.empty?
      @platforms.any? { |p| send("#{p}?") }
    end

    def to_lock
      out = "  #{name}"

      unless requirement == Gem::Requirement.default
        out << " (#{requirement.to_s})"
      end

      out << '!' if source

      out << "\n"
    end

  private

    def ruby?
      !mswin? && (!defined?(RUBY_ENGINE) || RUBY_ENGINE == "ruby" || RUBY_ENGINE == "rbx")
    end

    def ruby_18?
      ruby? && RUBY_VERSION < "1.9"
    end

    def ruby_19?
      ruby? && RUBY_VERSION >= "1.9"
    end

    def mri?
      !mswin? && (!defined?(RUBY_ENGINE) || RUBY_ENGINE == "ruby")
    end

    def mri_18?
      mri? && RUBY_VERSION < "1.9"
    end

    def mri_19?
      mri? && RUBY_VERSION >= "1.9"
    end

    def jruby?
      defined?(RUBY_ENGINE) && RUBY_ENGINE == "jruby"
    end

    def mswin?
      # w0t?
    end
  end
end
