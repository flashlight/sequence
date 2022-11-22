# Flashlight Sequence: Algorithms for Sequence Data

[**Quickstart**](#quickstart)
| [**Installation**](#building-and-installing)
| [**Python Documentation**](bindings/python)
| [**Citing**](#citing)

[![CircleCI](https://circleci.com/gh/flashlight/sequence.svg?style=shield)](https://app.circleci.com/pipelines/github/flashlight/sequence)
[![Join the chat at https://gitter.im/flashlight-ml/community](https://img.shields.io/gitter/room/flashlight-ml/community)](https://gitter.im/flashlight-ml/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) [![codecov](https://codecov.io/gh/flashlight/sequence/branch/main/graph/badge.svg?token=rBp4AilMc0)](https://codecov.io/gh/flashlight/sequence)

*Flashlight Sequence* is a library with fast implementations of sequence-based operations. It includes:
- A fast, parallel CPU implementation of the Viterbi algorithm for greedy "`argmax`-style" decoding
- Fast implementations (CPU and CUDA) of the [Wav2letter ASG loss](https://arxiv.org/pdf/1609.03193.pdf) function including the fully-connected and forced-alignment algorithms.

## Quickstart

Flashlight Sequence has Python bindings. To install the bindings from source, [optionally install CUDA] then clone the repo and build:
```shell
git clone https://github.com/flashlight/sequence && cd sequence
cd bindings/python
python setup.py install
```
To install with CUDA support, set the environment variable `USE_CUDA=1` when running the install command.

See the [full Python binding documentation](bindings/python) for examples and more.

## Building and Installing
[**From Source (C++)**](#building-from-source) | [**From Source (Python)**](bindings/python#build-instructions) | [**Adding to Your Own Project (C++)**](#adding-flashlight-sequence-to-a-c++-project)

### Requirements
At minimum, compilation requires:
- A C++ compiler with good C++17 support (e.g. gcc/g++ >= 7)
- [CMake](https://cmake.org/) — version 3.16 or later, and ``make``
- A Linux-based operating system.

**CUDA Support:** If building with CUDA support, CUDA >= 9 is recommended. To toggle CUDA support use the `FL_SEQUENCE_USE_CUDA` CMake option or the `USE_CUDA` environment variable when building the Python bindings.

**Tests:** If building tests, [Google Test](https://github.com/google/googletest) >= 1.12 is required, but is installed automatically on build if not found. The `FL_SEQUENCE_BUILD_TESTS` CMake option toggles building tests.

Instructions for building/installing the Python bindings from source [can be found here](bindings/python/README.md).

### Building from Source

Building the C++ project from source is simple:
```bash
git clone https://github.com/flashlight/sequence && cd sequence
mkdir build && cd build
cmake ..
make -j$(nproc)
make test    # run tests
make install # install at the CMAKE_INSTALL_PREFIX
```
To enable CUDA while building, pass `-DFL_SEQUENCE_USE_CUDA=ON` to CMake. To disable building tests, pass `-DFL_SEQUENCE_BUILD_TESTS=OFF`.

If building with CUDA < 11, [NVIDIA cub](https://github.com/NVIDIA/cub) is required. It will be downloaded automatically if not found; the `FL_SEQUENCE_BUILD_STANDALONE` build option controls this behavior.

### Adding Flashlight Sequence to a C++ Project

Given a simple `project.cpp` file that includes and links to Flashlight Sequence:
```c++
#include <iostream>

#include <flashlight/lib/sequence/criterion/cpu/ViterbiPath.h>

int main() {
  auto res = fl::lib::cpu::ViterbiPath<float>::compute(...);
  std::cout << "ViterbiPath result[0] " << res[0] << std::endl;
 return 0;
}
```

The following CMake configuration links Flashlight and sets include directories:

```cmake
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(myProject project.cpp)

find_package(flashlight-sequence CONFIG REQUIRED)
target_link_libraries(myProject PRIVATE flashlight::flashlight-sequence)
```

### Contributing and Contact
Contact: jacobkahn@fb.com

Flashlight Sequence is actively developed. See
[CONTRIBUTING](CONTRIBUTING.md) for more on how to help out.

## Citing
You can cite [Flashlight](https://arxiv.org/abs/2201.12465) using:
```
@misc{kahn2022flashlight,
      title={Flashlight: Enabling Innovation in Tools for Machine Learning},
      author={Jacob Kahn and Vineel Pratap and Tatiana Likhomanenko and Qiantong Xu and Awni Hannun and Jeff Cai and Paden Tomasello and Ann Lee and Edouard Grave and Gilad Avidov and Benoit Steiner and Vitaliy Liptchinsky and Gabriel Synnaeve and Ronan Collobert},
      year={2022},
      eprint={2201.12465},
      archivePrefix={arXiv},
      primaryClass={cs.LG}
}
```

For the AutoSegmentation Criterion (ASG), cite:
```
@article{collobert2016wav2letter,
  title={Wav2letter: an end-to-end convnet-based speech recognition system},
  author={Collobert, Ronan and Puhrsch, Christian and Synnaeve, Gabriel},
  journal={arXiv preprint arXiv:1609.03193},
  year={2016}
}
```

## License
Flashlight Sequence is under an MIT license. See [LICENSE](LICENSE) for more information.
