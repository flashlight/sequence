/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <cstddef>

#include "flashlight/lib/sequence/Defines.h"

namespace fl {
namespace lib {
namespace cpu {

template <class Float>
struct FL_SEQ_API ConnectionistTemporalClassificationCriterion {
  static size_t getWorkspaceSize(int B, int T, int N, int L);

  static void viterbi(
      int B,
      int T,
      int N,
      int L,
      const Float* input,
      const int* target,
      const int* targetSize,
      int* bestPaths,
      void* workspace);
};
} // namespace cpu
} // namespace lib
} // namespace fl
