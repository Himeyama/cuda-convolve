# frozen_string_literal: true

require_relative 'lib/cuda/convolve/version'

Gem::Specification.new do |spec|
  spec.name = 'cuda-convolve'
  spec.version       = CudaConvolve::VERSION
  spec.authors       = ['Murata Mitsuharu']
  spec.summary       = 'Use GPU for fast convolutional computation'
  spec.require_paths = %w[lib ext]
  spec.extensions = %w[ext/cuda/extconf.rb]
  spec.required_ruby_version = '>= 2.5'
  spec.license = 'MIT'

  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{\A(?:test|spec|features)/}) }
  end

  spec.add_development_dependency 'rake'
  spec.add_development_dependency 'rake-compiler'
end
