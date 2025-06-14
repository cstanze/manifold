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

#ifndef Manifold_Debug_hpp
#define Manifold_Debug_hpp

#include "_defines.hpp"
#include "os/fs.hpp"
#include <iostream>
#include <ostream>

class __nullstream : public std::ostream {
  __nullstream() : std::ostream(nullptr) {}
  ~__nullstream() override = default;

public:
  static auto get() -> std::ostream & {
    static __nullstream instance;
    return instance;
  }
};

#define ManifoldDebugLog                                                       \
  (ManifoldDebug ? std::cerr : __nullstream::get())                            \
      << "["                                                                   \
      << manifold::fs::relative_path(__filename__)                             \
             .value_or(std::filesystem::path("./invalid/path"))                \
      << ":" << __LINE__ << "@" << __funcname__ << "] "

#endif
