# frozen_string_literal: true

require_relative 'convolve/version'

# Convolve
module CudaConvolve
  require 'cuda/convolve.so'

  # Array
  refine Array do
    def convolve(ary, mode: :full, type: :float)
      modes = { full: 0, same: 1, valid: 2 }
      mode_n = modes[mode]
      raise "mode should be 'full', 'same', or 'valid'" unless mode_n

      case type
      when :float
        gpu_convolve_float(ary, mode_n)
      when :double
        gpu_convolve_double(ary, mode_n)
      else
        raise "type should be 'double' or 'float'"
      end
    end
  end
end

module Numo
  # DFloat
  class DFloat
    def convolve(ary, mode: :full)
      modes = { full: 0, same: 1, valid: 2 }
      mode_n = modes[mode]
      raise 'mode should be `full`, `same`, or `valid`' unless mode_n

      raise 'The only dimension that can be specified is 1' unless ndim == 1

      ary = self.class.cast(ary) unless ary.instance_of?(self.class)
      raise 'The only dimension that can be specified is 1' unless ary.ndim == 1

      gpu_convolve_double(ary, mode_n)
    end
  end
end
