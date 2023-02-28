cmake_minimum_required(VERSION 3.16)

project(flashlight-sequence LANGUAGES CXX C VERSION 0.1)

include(CTest)

# ----------------------------- Setup -----------------------------
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(FL_SEQUENCE_CODE_COVERAGE "Enable coverage reporting" OFF)

# Default directories for installation
set(FL_INSTALL_INC_DIR "include" CACHE PATH "Install path for headers")
set(FL_INSTALL_LIB_DIR "lib" CACHE PATH "Install path for libraries")
set(FL_INSTALL_BIN_DIR "bin" CACHE PATH "Install path for binaries")
# Other assets
set(FL_INSTALL_ASSETS_BASE_DIR "share/${PROJECT_NAME}")
set(FL_INSTALL_CMAKE_DIR "${FL_INSTALL_ASSETS_BASE_DIR}/cmake" CACHE PATH "Install path for CMake files")
set(FL_INSTALL_EXAMPLES_DIR "${FL_INSTALL_ASSETS_BASE_DIR}/examples" CACHE PATH "Install path for example files")
set(FL_INSTALL_DOC_DIR "${FL_INSTALL_ASSETS_BASE_DIR}/doc" CACHE PATH "Install path for documentation")

include(${PROJECT_SOURCE_DIR}/cmake/InternalUtils.cmake)

# ----------------------------- Configuration -----------------------------

option(FL_SEQUENCE_USE_CUDA "Build with CUDA support" OFF)
option(FL_SEQUENCE_BUILD_TESTS "Build tests" ON)
option(FL_SEQUENCE_BUILD_PYTHON "Build Python bindings" OFF)
option(FL_SEQUENCE_BUILD_STANDALONE "Build standalone installation" ON)
option(FL_SEQUENCE_BUILD_PYTHON_PACKAGE "Build packaging-ready Python artifacts" OFF)

# ------------------------ Build ------------------------

add_library(flashlight-sequence)

set_target_properties(flashlight-sequence PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  )

target_include_directories(
  flashlight-sequence
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  )

if (FL_SEQUENCE_USE_CUDA)
  enable_language(CUDA)

  # To support nvcc with CUDA < 11
  set_target_properties(
    flashlight-sequence
    PROPERTIES
    CUDA_STANDARD 14
    CUDA_STANDARD_REQUIRED ON
    )

  target_compile_definitions(
    flashlight-sequence
    PUBLIC
    FL_SEQUENCE_USE_CUDA
  )
endif()

include(${PROJECT_SOURCE_DIR}/flashlight/lib/sequence/CMakeLists.txt)

if (FL_SEQUENCE_BUILD_PYTHON)
  include(${PROJECT_SOURCE_DIR}/bindings/python/CMakeLists.txt)
endif()

add_library(flashlight::flashlight-sequence ALIAS flashlight-sequence)

# ------------------------ Tests + Code Coverage------------------------

if (FL_SEQUENCE_BUILD_TESTS)
  enable_testing()
  include(TestUtils)
  # TODO: add back after moving tests from Flashlight core
  # add_subdirectory(${PROJECT_SOURCE_DIR}/flashlight/lib/sequence/test)
endif()

if (FL_SEQUENCE_CODE_COVERAGE)
  fl_sequence_add_coverage_to_target(TARGET flashlight-sequence)
endif()

# ------------------------ Installation ------------------------

# Install headers
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/flashlight/lib
  COMPONENT headers
  DESTINATION ${FL_INSTALL_INC_DIR}/flashlight
  FILES_MATCHING # preserve directory structure
  PATTERN "*.h"
  PATTERN "*.hpp"
  PATTERN "*.cuh"
  PATTERN "test*" EXCLUDE
  PATTERN ".git" EXCLUDE
)

# Install libraries and create CMake config/targets files
fl_sequence_setup_install_targets(INSTALL_TARGETS flashlight-sequence)
