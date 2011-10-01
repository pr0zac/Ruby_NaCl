require 'rake'

Gem::Specification.new do |s|
  s.name = "ruby_nacl"
  s.version = "0.1.0"
  s.date = "2011-09-30"
  s.authors = ["Zac Morris"]
  s.email = "zac@caffeinatedmind.com"
  s.summary = "Ruby NaCl library."
  s.homepage = "http://github.com/CaffeinatedMind/ruby_nacl"
  s.description = "Provides a ruby interface to DJB's NaCl library."
  s.files = [ "README.md", "Changelog"] + FileList["ext/**/*"].to_a
  s.extensions = ['ext/ruby_nacl/extconf.rb']
  s.add_dependency('rice', '>= 1.4.2')
end
