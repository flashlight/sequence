/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#if defined(_WIN32) || defined(_MSC_VER)

#ifdef FL_SEQ_DLL
#define FL_SEQ_API __declspec(dllexport)
#else // FL_SEQ_DLL
#define FL_SEQ_API __declspec(dllimport)
#endif // FL_SEQ_DLL

#define FL_SEQ_DEPRECATED(msg) __declspec(deprecated(msg)

#else // defined(_WIN32) || defined(_MSC_VER)

#define FL_SEQ_API __attribute__((visibility("default")))
#define FL_SEQ_DEPRECATED(msg) __attribute__((deprecated(msg)))

#endif // defined(_WIN32) || defined(_MSC_VER)
