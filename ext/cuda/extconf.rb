# frozen_string_literal: true

require 'mkmf'

create_makefile('convolve') if have_library('cuda-convolve')
