/**
 *  MIT License
 *
 * Copyright (c) 2025 Jules Nieves
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/

#ifndef _MANIFOLD_DEFINES_H_
#define _MANIFOLD_DEFINES_H_

#include <stddef.h>
#include <stdint.h>

#ifndef ManifoldDebug
#define ManifoldDebug false
#endif

#if defined(_WIN32) || defined(_WIN64)
#define MANIFOLD_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
#define MANIFOLD_PLATFORM_APPLE
#elif defined(__linux__)
#define MANIFOLD_PLATFORM_LINUX
#elif defined(__unix__)
#define MANIFOLD_PLATFORM_UNIX
#else
#error "Unknown platform"
#endif

#ifndef __funcname__
#ifdef MANIFOLD_PLATFORM_WINDOWS
#define __funcname__ __FUNCTION__
#else
#define __funcname__ __func__
#endif
#endif

#ifndef __filename__
#ifdef MANIFOLD_PLATFORM_WINDOWS
#define __filename__ __FILE__
#else
#define __filename__ __FILE__
#endif
#endif

#if defined(__clang__)
#define MANIFOLD_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define MANIFOLD_COMPILER_GCC
#elif defined(_MSC_VER)
#define MANIFOLD_COMPILER_MSVC
#else
#error "Unknown compiler"
#endif

#if defined(MANIFOLD_COMPILER_CLANG) || defined(MANIFOLD_COMPILER_GCC)
#define MANIFOLD_DEPRECATED __attribute__((deprecated))
#elif defined(MANIFOLD_COMPILER_MSVC)
#define MANIFOLD_DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: MANIFOLD_DEPRECATED not supported for this compiler")
#define MANIFOLD_DEPRECATED
#endif

#if defined(MANIFOLD_COMPILER_CLANG) || defined(MANIFOLD_COMPILER_GCC)
#define MANIFOLD_NORETURN __attribute__((noreturn))
#elif defined(MANIFOLD_COMPILER_MSVC)
#define MANIFOLD_NORETURN __declspec(noreturn)
#else
#pragma message("WARNING: MANIFOLD_NORETURN not supported for this compiler")
#define MANIFOLD_NORETURN
#endif

#if __cplusplus
#define MANIFOLDC extern "C" {
#define MANIFOLDC_END }
#else
#define MANIFOLDC
#define MANIFOLDC_END
#endif

#if defined(MANIFOLD_COMPILER_CLANG) || defined(MANIFOLD_COMPILER_GCC)
#if __has_builtin(__builtin_unreachable)
#define MANIFOLD_UNREACHABLE __builtin_unreachable()
#else
#define MANIFOLD_UNREACHABLE for (;;) // technically UB, but works
#endif
#elif defined(MANIFOLD_COMPILER_MSVC)
#define MANIFOLD_UNREACHABLE __assume(0)
#else
#pragma message("WARNING: MANIFOLD_UNREACHABLE not supported for this compiler")
#define MANIFOLD_UNREACHABLE
#endif

#if defined(MANIFOLD_COMPILER_CLANG) || defined(MANIFOLD_COMPILER_GCC)
#define MANIFOLD_ASSERT(x)                                                        \
  ((x) ? (void)0 : __assert_fail(#x, __filename__, __LINE__, __funcname__))
#elif defined(MANIFOLD_COMPILER_MSVC)
#define MANIFOLD_ASSERT(x) ((x) ? (void)0 : __assert(#x, __filename__, __LINE__))
#else
#pragma message("WARNING: MANIFOLD_ASSERT not supported for this compiler")
#define MANIFOLD_ASSERT(x) ((void)0)
#endif

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long;
using usize = size_t;
using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long;
using isize = ptrdiff_t;
using f32 = float;
using f64 = double;

#endif
