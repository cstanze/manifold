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

#ifndef Manifold_Bitflags_hpp
#define Manifold_Bitflags_hpp

#include "../_defines.hpp"
#include "../concepts.hpp"
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace manifold::adt {

using namespace manifold::concepts;

/// A "bitflags"-like type that can be used with enums (not compatible with enum class)
template <BitFlagConvertible T> class BitFlags {
  u64 flags;

public:
  constexpr BitFlags() : flags(0) {}

  template<typename... Args>
  constexpr BitFlags(Args... flags)
    : flags((... | (raw_flag(flags))))
    {
      static_assert((std::is_same_v<T, Args> && ...), "All arguments must be of the same type T");
    }
  
  constexpr BitFlags(std::initializer_list<T> flags_) {
    for (T flag : flags_)
      flags |= flag;
  }

  constexpr BitFlags(const BitFlags &other) : flags(other.flags) {}

  constexpr auto operator=(const BitFlags &other) -> BitFlags & {
    flags = other.flags;
    return *this;
  }

  constexpr auto operator==(const BitFlags &other) const -> bool {
    return flags == other.flags;
  }

  constexpr auto operator!=(const BitFlags &other) const -> bool {
    return flags != other.flags;
  }

  constexpr auto operator[](T flag) const -> bool {
    return contains(flag);
  }

  constexpr auto set(T flag, bool value = true) -> void {
    if (value)
      flags |= raw_flag(flag);
    else
      flags &= ~raw_flag(flag);
  }

  constexpr auto contains(T flag) const -> bool {
    return flags & raw_flag(flag);
  }

  constexpr auto empty() const -> bool { return flags == 0; }

  constexpr auto clear() -> void { flags = 0; }

  constexpr auto raw() const -> u64 { return flags; }

  constexpr auto raw_flag(T flag) const -> u64 { return (1 << static_cast<u64>(flag)); }
};

}

#endif
