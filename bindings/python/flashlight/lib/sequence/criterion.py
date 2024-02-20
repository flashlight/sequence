#!/usr/bin/env python3
"""
Copyright (c) Facebook, Inc. and its affiliates.

This source code is licensed under the MIT-style license found in the
LICENSE file in the root directory of this source tree.
"""


have_torch = False
try:

    have_torch = True
except ImportError:
    pass

if have_torch:
    pass
