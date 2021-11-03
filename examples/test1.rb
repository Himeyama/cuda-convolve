# frozen_string_literal: true

require 'bundler/setup'
require 'numo/narray'
require 'cuda/convolve'

using CudaConvolve

p [1, 2, 3].convolve([0, 1, 0.5])

p Numo::DFloat[1, 2, 3].convolve([0, 1, 0.5])

# p Numo::DFloat[1, 2, 3].methods.sort
