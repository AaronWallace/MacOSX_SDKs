module Bundler
  class UI
    def warn(message)
    end

    def error(message)
    end

    def info(message)
    end

    def confirm(message)
    end

    class Shell < UI
      def initialize(shell)
        @shell = shell
        @quiet = false
      end

      def debug(msg)
        @shell.say(msg) if ENV['DEBUG'] && !@quiet
      end

      def info(msg)
        @shell.say(msg) if !@quiet
      end

      def confirm(msg)
        @shell.say(msg, :green) if !@quiet
      end

      def warn(msg)
        @shell.say(msg, :yellow)
      end

      def error(msg)
        @shell.say(msg, :red)
      end

      def be_quiet!
        @quiet = true
      end
    end

    class RGProxy < Gem::SilentUI
      def initialize(ui)
        @ui = ui
      end

      def say(message)
        if message =~ /native extensions/
          @ui.info "with native extensions "
        else
          @ui.debug(message)
        end
      end
    end
  end
end
