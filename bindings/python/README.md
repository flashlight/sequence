# Flashlight Sequence Python Bindings
**Contents**
- [Installation](#installation)
  * [Dependencies](#dependencies)
  * [Build Instructions](#build-instructions)
  * [Advanced Options](#advanced-options)
- [Python API Documentation](#python-api-documentation)

## Installation
CUDA is required if building CUDA kernel implementations with the Python package.

### Build Instructions
From the project root, run:
```
pip install .
```

or locally in editable mode (`-e` is required as libs are built outside of the bindings directory)
```
pip install -e .
```

(`pypi` installation coming soon)

### Advanced Options
- `USE_CUDA=1` builds CUDA kernels for many included algorithms. CUDA >= 9 is required.

## Python API Documentation

Coming soon.
