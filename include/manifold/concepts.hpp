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

#ifndef Manifold_Concepts_hpp
#define Manifold_Concepts_hpp

#include "_defines.hpp"
#include <concepts>
#include <ostream>

namespace manifold::concepts {

/// same as above, but allows *any* type that can satisfy static_cast<u64>(t)
template <typename T>
concept BitFlagConvertible =
    (std::is_enum<T>::value && std::is_convertible<T, u64>::value) ||
    requires(T t) {
      {
        static_cast<u64>(t)
      }; // e.g. enum class with underlying type u64 (uint64_t)
    };

/// pulled from c++23, see "Possible implementation"
/// http://cppreference.com/w/cpp/types/is_scoped_enum.html
namespace __detail {
void test_conversion(...);          // selected when E is complete and scoped
void test_conversion(int) = delete; // selected when E is complete but unscoped

template <class E>
concept is_scoped_enum_impl =
    std::is_enum_v<E> && requires { __detail::test_conversion(E{}); };

} // namespace __detail

template <class T>
struct is_scoped_enum : std::bool_constant<__detail::is_scoped_enum_impl<T>> {};

/// for tagged unions, we try to follow rust-like tagging standards (e.g.
/// accompanying `enum class`)
template <typename T>
concept TaggedUnionConvertible =
    is_scoped_enum<T>::value && std::is_convertible<T, u64>::value;

/// `S` printable types (`S << T`), default `S = std::ostream`
template <typename T, typename S = std::ostream>
concept Printable = requires(S &os, T t) {
  { os << t };
};

/// T must be comparable with `==`, `!=`
template <typename T>
concept EqualityComparable = std::equality_comparable<T>;

/// T must be copyable
template <typename T>
concept CopyConstructible = std::copy_constructible<T>;

/// T must be movable
template <typename T>
concept MoveConstructible = std::move_constructible<T>;

} // namespace manifold::concepts

#endif
