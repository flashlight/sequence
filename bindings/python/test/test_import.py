"""
Copyright (c) Facebook, Inc. and its affiliates.
This source code is licensed under the MIT-style license found in the
LICENSE file in the root directory of this source tree.
"""

import logging
import os
import unittest


class ImportTestCase(unittest.TestCase):
    def test_import_lib_sequence(self):
        from flashlight.lib.sequence import criterion
        from flashlight.lib.sequence.criterion import (
            CpuForceAlignmentCriterion,
            CpuFullConnectionCriterion,
            CpuViterbiPath,
            CriterionScaleMode,
        )

        if os.getenv("USE_CUDA", "OFF").upper() not in [
            "OFF",
            "0",
            "NO",
            "FALSE",
            "N",
        ]:
            from flashlight.lib.sequence.flashlight_lib_sequence_criterion import (
                CudaForceAlignmentCriterion,
                CudaFullConnectionCriterion,
                CudaViterbiPath,
            )
        else:
            logging.info("Flashlight Sequence bindings built without CUDA")


if __name__ == "__main__":
    unittest.main()
