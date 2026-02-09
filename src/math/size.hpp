// src/math/size.hpp
// SPDX-License-Identifier: Zlib
//
// ClanLib SDK
// Copyright (c) 1997-2005 The ClanLib Team
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
// File Author(s):
//   Magnus Norddahl
//   (if your name is missing here, please add it)

#ifndef HEADER_PINGUS_MATH_SIZE_HPP
#define HEADER_PINGUS_MATH_SIZE_HPP

#include <iosfwd>

namespace pingus {


class Sizef;

//: 2D (width,height) size structure.
//- !group=Core/Math!
//- !header=core.h!
class Size
{
  //! Construction:
public:
  //: Constructs a size structure.
  //param width: Initial width of size structure.
  //param height: Initial height of size structure.
  //param size: Size structure to construct this one from.
  constexpr Size() noexcept
    : width(0), height(0)
  {}

  constexpr Size(int width_, int height_) noexcept
    : width(width_), height(height_)
  {}

  Size(const Size&) = default;
  Size& operator=(const Size&) = default;

  explicit Size(const Sizef& s);

  //! Attributes:
public:
  //: Size width.
  int width;

  //: Size height.
  int height;

  //! Operations:
public:
  //: Size += Size operator.
  constexpr Size &operator+=(const Size &s) noexcept
  { width += s.width; height += s.height; return *this; }

  //: Size -= Size operator.
  constexpr Size &operator-=(const Size &s) noexcept
  { width -= s.width; height -= s.height; return *this; }

  //: Size + Size operator.
  constexpr Size operator+(const Size &s) const noexcept
  { return Size(width + s.width, height + s.height); }

  //: Size - Size operator.
  constexpr Size operator-(const Size &s) const noexcept
  { return Size(width - s.width, height - s.height); }

  //: Size == Size operator (deep compare).
  constexpr bool operator==(const Size &s) const noexcept
  { return (width == s.width) && (height == s.height); }

  //: Size != Size operator (deep compare).
  constexpr bool operator!=(const Size &s) const noexcept
  { return (width != s.width) || (height != s.height); }

  //: Size / int operator.
  constexpr Size operator/(int a) noexcept
  { return Size(width / a, height / a); }

  //: Size /= Size operator.
  constexpr Size &operator/=(int a) noexcept
  { width /= a; height /= a; return *this; }

  constexpr int get_area() const noexcept { return width * height; }
};

//: 2D (width,height) floating point size structure.
class Sizef
{
  //! Construction:
public:
  //: Constructs a size structure.
  //param width: Initial width of size structure.
  //param height: Initial height of size structure.
  //param size: Size structure to construct this one from.
  constexpr Sizef() noexcept
    : width(0.0f),
      height(0.0f)
  {}

  constexpr Sizef(const Size& s) noexcept
    : width(static_cast<float>(s.width)),
      height(static_cast<float>(s.height))
  {}

  constexpr Sizef(float width_, float height_) noexcept
    : width(width_),
      height(height_)
  {}

  Sizef(const Sizef&) = default;
  Sizef& operator=(const Sizef&) = default;

  //! Attributes:
public:
  //: Size width.
  float width;

  //: Size height.
  float height;

  //! Operations:
public:
  //: Size += Size operator.
  constexpr Sizef &operator+=(const Sizef &s) noexcept
  { width += s.width; height += s.height; return *this; }

  //: Size -= Size operator.
  constexpr Sizef &operator-=(const Sizef &s) noexcept
  { width -= s.width; height -= s.height; return *this; }

  //: Size + Size operator.
  constexpr Sizef operator+(const Sizef &s) const noexcept
  { return Sizef(width + s.width, height + s.height); }

  //: Size - Size operator.
  constexpr Sizef operator-(const Sizef &s) const noexcept
  { return Sizef(width - s.width, height - s.height); }

  //: Size == Size operator (deep compare).
  constexpr bool operator==(const Sizef &s) const noexcept
  { return (width == s.width) && (height == s.height); }

  //: Size != Size operator (deep compare).
  constexpr bool operator!=(const Size &s) const noexcept
  { return (width != s.width) || (height != s.height); }

  //: Size *= Size operator.
  constexpr Sizef &operator*=(float v) noexcept
  { width *= v; height *= v; return *this; }

  //: Size /= Size operator.
  constexpr Sizef &operator/=(float v) noexcept
  { width /= v; height /= v; return *this; }
};

constexpr Sizef operator*(const Sizef& s, float f) noexcept
{
  return Sizef(s.width * f, s.height * f);
}

inline Size::Size(const Sizef& s)
  : width(static_cast<int>(s.width)),
    height(static_cast<int>(s.height))
{}

std::ostream& operator<<(std::ostream& s, const Size& size);


} // namespace pingus
#endif

// EOF
