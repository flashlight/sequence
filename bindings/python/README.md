# Flashlight Sequence Python Bindings
**Contents**
- [Installation](#installation)
  * [Dependencies](#dependencies)
  * [Build Instructions](#build-instructions)
  * [Advanced Options](#advanced-options)
- [Python API Documentation](#python-api-documentation)

## Installation
### Dependencies
`python >= 3.6` is required with the following packages installed:
- [packaging](https://pypi.org/project/packaging/)
- [cmake](https://cmake.org/) >= 3.16, and `make`
- CUDA is optionally required.

### Build Instructions

Once the dependencies are satisfied, from the project root, use:
```
cd bindings/python
python setup.py install
```

or locally in editable mode (`-e` is required as libs are built outside of the bindings directory)
```
pip install -e .
```

(`pypi` installation coming soon)

**Note:** if you encounter errors, you'll probably have to `rm -rf build dist` before retrying the install.

### Advanced Options
- `USE_CUDA=1` builds CUDA kernels for many included algorithms. CUDA >= 9 is required.

## Python API Documentation

Coming soon.
