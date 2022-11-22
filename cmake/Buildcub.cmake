cmake_minimum_required(VERSION 3.16)

include(FetchContent)

FetchContent_Declare(
  cub
  GIT_REPOSITORY https://github.com/NVIDIA/cub.git
  # guaranteed to work with CUDA < 11, where it isn't bundled
  GIT_TAG        1.8.0
  )

FetchContent_MakeAvailable(cub)
set(cub_INCLUDE_DIRS ${cub_SOURCE_DIR})
