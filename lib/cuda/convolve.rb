# frozen_string_literal: true

require_relative 'cuda/convolve/version'

# Convolve
module CudaConvolve
  # Array
  class Array
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
