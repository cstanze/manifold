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

#ifndef Manifold_String_hpp
#define Manifold_String_hpp

#include "../_defines.hpp"
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

namespace manifold::str {

/// Checks if a string ends with a certain substring
auto ends_with(const std::string &str, const std::string &suffix) -> bool;

/// Checks if a string starts with a certain substring
auto starts_with(const std::string &str, const std::string &prefix) -> bool;

/// Splits a string into a vector of strings
auto split(const std::string &str, const std::string &delim)
    -> std::vector<std::string>;

/// Replaces all occurrences of a substring in a string
auto replace_all(const std::string &str, const std::string &from,
                 const std::string &to) -> std::string;

/// Joins a vector of strings into a single string
auto join(const std::vector<std::string> &strs, const std::string &delim = "")
    -> std::string;

/// Converts a string to lowercase
auto to_lower(const std::string &str) -> std::string;

/// Converts a string to uppercase
auto to_upper(const std::string &str) -> std::string;

/// Trims whitespace from the beginning and end of a string
auto trim(const std::string &str) -> std::string;

/// Converts a string to a C-style string **by copying it**
auto as_cstr(const std::string &str) -> const i8 *;

} // namespace manifold::str

#endif
