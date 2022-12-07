cmake_minimum_required(VERSION 3.16)

find_package(OpenMP REQUIRED)
target_link_libraries(flashlight-sequence PRIVATE OpenMP::OpenMP_CXX)

target_sources(
  flashlight-sequence
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/cpu/CriterionUtils.cpp
  ${CMAKE_CURRENT_LIST_DIR}/cpu/ForceAlignmentCriterion.cpp
  ${CMAKE_CURRENT_LIST_DIR}/cpu/ConnectionistTemporalClassificationCriterion.cpp
  ${CMAKE_CURRENT_LIST_DIR}/cpu/FullConnectionCriterion.cpp
  ${CMAKE_CURRENT_LIST_DIR}/cpu/ViterbiPath.cpp
  )

if (FL_SEQUENCE_USE_CUDA)
  # cub is required for BlockReduce and not bundled with CUDA < 11
  find_path(cub_INCLUDE_DIRS
    NAMES cub.cuh
    PATH_SUFFIXES cub include
    PATHS ${cub_BASE_DIR} ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
    ENV ${cub_BASE_DIR})
  if (NOT cub_INCLUDE_DIRS)
    if (NOT FL_SEQUENCE_BUILD_STANDALONE)
      message(FATAL_ERROR
        "Required dependency NVIDIA cub not found - try setting cub_BASE_DIR")
    endif()

    message(STATUS "NVIDIA cub not found - downloading from source")
    include(${PROJECT_SOURCE_DIR}/cmake/Buildcub.cmake)
    target_include_directories(flashlight-sequence PRIVATE ${cub_INCLUDE_DIRS})
  else()
    message(STATUS "NVIDIA cub found: (include: ${cub_INCLUDE_DIRS})")
  endif()

  target_sources(
    flashlight-sequence
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/cuda/CriterionUtils.cu
    ${CMAKE_CURRENT_LIST_DIR}/cuda/ForceAlignmentCriterion.cu
    ${CMAKE_CURRENT_LIST_DIR}/cuda/FullConnectionCriterion.cu
    ${CMAKE_CURRENT_LIST_DIR}/cuda/ViterbiPath.cu
    )

  target_include_directories(
    flashlight-sequence
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}>
    )
endif()
