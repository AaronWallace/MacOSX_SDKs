require 'contest'
require 'tilt'

begin
  require 'coffee_script'

  class CoffeeScriptTemplateTest < Test::Unit::TestCase
    test "is registered for '.coffee' files" do
      assert_equal Tilt::CoffeeScriptTemplate, Tilt['test.coffee']
    end

    test "compiles and evaluates the template on #render" do
      template = Tilt::CoffeeScriptTemplate.new { |t| "puts 'Hello, World!'\n" }
      assert_match "puts('Hello, World!');", template.render
    end

    test "can be rendered more than once" do
      template = Tilt::CoffeeScriptTemplate.new { |t| "puts 'Hello, World!'\n" }
      3.times { assert_match "puts('Hello, World!');", template.render }
    end

    test "disabling coffee-script wrapper" do
      template = Tilt::CoffeeScriptTemplate.new(:no_wrap => true) { |t| "puts 'Hello, World!'\n" }
      assert_equal "puts('Hello, World!');", template.render
    end
  end

rescue LoadError => boom
  warn "Tilt::CoffeeScriptTemplate (disabled)\n"
end
