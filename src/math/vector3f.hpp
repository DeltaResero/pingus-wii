// src/math/vector3f.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_MATH_VECTOR3F_HPP
#define HEADER_PINGUS_MATH_VECTOR3F_HPP

#include "math/vector2f.hpp"

namespace pingus {


class Vector3f
{
public:
  float x;
  float y;
  float z;

public:
  explicit constexpr Vector3f (float x_=0, float y_=0, float z_=0) noexcept : x(x_), y(y_), z(z_) {}

  constexpr Vector3f (const Vector3f& old) noexcept : x(old.x), y(old.y), z(old.z) {}
  constexpr Vector3f (const Vector2f& old) noexcept : x(old.x), y(old.y), z(0) {}
  constexpr Vector3f (const Vector2i& old) noexcept : x(float(old.x)), y(float(old.y)), z(0) {}
  constexpr Vector3f& operator= (const Vector3f& old) noexcept
  {
    if (this != &old)
    {
      x = old.x;
      y = old.y;
      z = old.z;
    }

    return *this;
  }

  constexpr Vector3f operator- () const noexcept
  {
    return Vector3f(-x, -y, -z);
  }

  constexpr Vector3f operator+ (const Vector3f& add) const noexcept
  {
    return Vector3f(x + add.x, y + add.y, z + add.z);
  }
  constexpr Vector3f operator- (const Vector3f& sub) const noexcept
  {
    return Vector3f(x - sub.x, y - sub.y, z - sub.z);
  }
  constexpr Vector3f operator* (float mul) const noexcept
  {
    return Vector3f(mul * x, mul * y, mul * z);
  }

  constexpr Vector3f& operator+= (const Vector3f& add) noexcept
  {
    x += add.x;
    y += add.y;
    z += add.z;
    return *this;
  }
  constexpr Vector3f& operator-= (const Vector3f& sub) noexcept
  {
    x -= sub.x;
    y -= sub.y;
    z -= sub.z;
    return *this;
  }
  constexpr Vector3f& operator*= (float mul) noexcept
  {
    x *= mul;
    y *= mul;
    z *= mul;
    return *this;
  }

  void normalize ()
  {
    float f = std::sqrt(x * x + y * y + z * z);

    if (f != 0.0f)
    {
      x /= f;
      y /= f;
      z /= f;
    }
  }

  float length() const
  {
    return std::sqrt(x * x + y * y + z * z);
  }

  Vector3f rotate (float angle, const Vector3f& pos) const;

  static float distance(const Vector3f& a, const Vector3f& b)
  {
    float x = b.x - a.x;
    float y = b.y - a.y;
    float z = b.z - a.z;

    return std::sqrt((x * x) + (y * y) + (z * z));
  }
  static float distance2d(const Vector3f& a, const Vector3f& b)
  {
    float x = b.x - a.x;
    float y = b.y - a.y;

    return std::sqrt((x * x) + (y * y));
  }

  /** Calculate a position between a and b, relative to the value of
      \a perc (perc == 0 -> a, perc == 1.0 -> b) */
  static constexpr Vector3f interpolate(const Vector3f& a, const Vector3f& b, float perc) noexcept
  {
    Vector3f c = b - a;
    return a + (c * perc);
  }
};

std::ostream& operator<< (std::ostream& os, const Vector3f& v);


} // namespace pingus
#endif

// EOF
