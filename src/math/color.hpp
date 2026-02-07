// src/math/color.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_MATH_COLOR_HPP
#define HEADER_PINGUS_MATH_COLOR_HPP

#include <SDL.h>

namespace pingus {

class Color
{
public:
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  Color()
    : r(0), g(0), b(0), a(255)
  {}

  Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255)
    : r(r_), g(g_), b(b_), a(a_)
  {}

  bool operator==(const Color& rhs) const {
    return
      r == rhs.r &&
      g == rhs.g &&
      b == rhs.b &&
      a == rhs.a;
  }
};


} // namespace pingus
#endif

// EOF
