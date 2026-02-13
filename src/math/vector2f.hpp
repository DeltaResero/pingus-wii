// src/math/vector2f.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2004 Matthias Braun <matze@braunis.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_MATH_VECTOR2F_HPP
#define HEADER_PINGUS_MATH_VECTOR2F_HPP

#include "math/math.hpp"
#include "vector2i.hpp"

namespace pingus {


/** Simple two dimensional vector. */
class Vector2f
{
public:
  constexpr Vector2f(float nx, float ny) noexcept
    : x(nx), y(ny)
  { }
  constexpr Vector2f(const Vector2f& other) noexcept = default;
  constexpr Vector2f(Vector2i other) noexcept
    : x(static_cast<float>(other.x)),
      y(static_cast<float>(other.y))
  {}
  constexpr Vector2f() noexcept
    : x(0), y(0)
  { }

  constexpr bool operator ==(Vector2f other) const noexcept
  {
    return x == other.x && y == other.y;
  }

  constexpr bool operator !=(Vector2f other) const noexcept
  {
    return !(x == other.x && y == other.y);
  }

  constexpr Vector2f& operator=(const Vector2f& other) noexcept = default;

  constexpr Vector2f operator+(Vector2f other) const noexcept
  {
    return Vector2f(x + other.x, y + other.y);
  }

  constexpr Vector2f operator-(Vector2f other) const noexcept
  {
    return Vector2f(x - other.x, y - other.y);
  }

  constexpr Vector2f operator*(float s) const noexcept
  {
    return Vector2f(x * s, y * s);
  }

  constexpr Vector2f operator/(float s) const noexcept
  {
    return Vector2f(x / s, y / s);
  }

  constexpr Vector2f operator-() const noexcept
  {
    return Vector2f(-x, -y);
  }

  constexpr Vector2f& operator +=(Vector2f other) noexcept
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  constexpr Vector2f& operator -=(Vector2f other) noexcept
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  constexpr Vector2f& operator *=(float val) noexcept
  {
    x *= val;
    y *= val;
    return *this;
  }

  constexpr Vector2f& operator /=(float val) noexcept
  {
    x /= val;
    y /= val;
    return *this;
  }

  /** Takes angle in radian and returns a copy of the vector rotated
      by \a angle */
  Vector2f rotate(float angle) const
  {
    float len = magnitude();
    return Vector2f(len * std::cos(angle), len * std::sin(angle));
  }

  /// Scalar product of 2 vectors
  constexpr float operator*(Vector2f other) const noexcept
  {
    return x*other.x + y*other.y;
  }

  float magnitude() const
  {
    return std::sqrt(x*x + y*y);
  }
  float length() const { return magnitude(); }

  Vector2f unit() const
  {
    return *this / magnitude();
  }
  void normalize()
  {
    float mag = magnitude();
    x /= mag;
    y /= mag;
  }

  float x, y;
};

std::ostream& operator<<(std::ostream& s, Vector2f v);


} // namespace pingus
#endif

// EOF
