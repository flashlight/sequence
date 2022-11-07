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
