// src/math/vector2i.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_MATH_VECTOR2I_HPP
#define HEADER_PINGUS_MATH_VECTOR2I_HPP

#include <ostream>

namespace pingus {


class Vector2f;

class Vector2i
{
public:
  int x;
  int y;

  constexpr Vector2i() noexcept
    : x(0), y(0) {}

  explicit Vector2i(const Vector2f& v);

  constexpr Vector2i(int x_, int y_) noexcept
    : x(x_), y(y_) {}

  constexpr Vector2i operator+ (Vector2i add) const noexcept
  {
    return Vector2i(x + add.x, y + add.y);
  }

  constexpr Vector2i operator- () const noexcept
  {
    return Vector2i(-x, -y);
  }

  constexpr Vector2i operator- (Vector2i sub) const noexcept
  {
    return Vector2i(x - sub.x, y - sub.y);
  }

  constexpr Vector2i operator* (int  mul) const noexcept
  {
    return Vector2i(x * mul, y * mul);
  }

  constexpr Vector2i& operator+= (Vector2i add) noexcept
  {
    x += add.x;
    y += add.y;
    return *this;
  }

  constexpr Vector2i& operator-= (Vector2i sub) noexcept
  {
    x -= sub.x;
    y -= sub.y;
    return *this;
  }

  constexpr Vector2i& operator*= (int mul) noexcept
  {
    x *= mul;
    y *= mul;
    return *this;
  }

  constexpr bool operator== (Vector2i other) const noexcept
  {
    return (other.x == x && other.y == y);
  }

  constexpr bool operator!= (Vector2i other) const noexcept
  {
    return (other.x != x || other.y != y);
  }
};

std::ostream& operator<<(std::ostream& s, Vector2i v);


} // namespace pingus
#endif

// EOF
