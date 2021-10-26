# frozen_string_literal: true

require 'cuda/convolve'

using CudaConvolve

p [1, 2, 3].convolve([0, 1, 0.5])
