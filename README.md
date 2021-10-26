# cuda-convolve

## Installation

### Dependency
```bash
brew install himeyama/homebrew-lib/libcuda-convolve
```

### Gem or Gemfile
> Gemfile
```rb
gem 'cuda-convolve'
```

and

```bash
bundle
```

> Gem
```bash
gem install cuda-convolve
```

## Examples
```rb
# frozen_string_literal: true

require 'cuda/convolve'

using CudaConvolve

p [1, 2, 3].convolve([0, 1, 0.5])
# [0.0, 1.0, 2.5, 4.0, 1.5]
```

```rb
p [1, 2, 3].convolve([0, 1, 0.5], mode: :same)
# [1.0, 2.5, 4.0]
```

```rb
p [1, 2, 3].convolve([0, 1, 0.5], mode: :valid)
# [2.5]
```

