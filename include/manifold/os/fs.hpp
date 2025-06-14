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

#ifndef Manifold_Filesystem_hpp
#define Manifold_Filesystem_hpp

#include "../_defines.hpp"
#include "../adt/result.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace manifold::fs {

enum class Error { NoFileExists };

using path_type = std::filesystem::path;

/// Return the current working directory
auto cwd() -> path_type;

/// Returns the home directory of the current user
auto home() -> path_type;

/// Reads a file into a string (blocking)
auto read_file(const path_type &path)
    -> manifold::result<std::string, fs::Error>;

/// Reads a file into a byte vector (blocking)
auto read_file_bytes(const path_type &path)
    -> manifold::result<std::vector<u8>, fs::Error>;

/// Write a byte vector to a file
auto write_bytes(const path_type &path, const std::vector<u8> &bytes)
    -> manifold::result<void, fs::Error>;

/// Check if a path exists
auto path_exists(const path_type &path) -> bool;

/// Return the relative path of a file in a directory (or cwd if not specified)
auto relative_path(const path_type &path, const path_type &ref = cwd())
    -> manifold::result<path_type, fs::Error>;

/// Returns the absolute path of a file (error if it doesn't exist)
auto absolute_path(const path_type &path)
    -> manifold::result<path_type, fs::Error>;

/// Returns true if path is absolute
auto is_absolute(const path_type &path) -> bool;

/// Returns true if path is relative
auto is_relative(const path_type &path) -> bool;

/// Returns true if path is a directory
auto is_dir(const path_type &path) -> bool;

/// Returns true if path is a file
auto is_file(const path_type &path) -> bool;

/// Searches for a file in a dir using a matcher functon
auto search(const path_type &dir,
            const std::function<bool(const path_type &)> &matcher)
    -> manifold::result<path_type, fs::Error>;

} // namespace manifold::fs

#endif
