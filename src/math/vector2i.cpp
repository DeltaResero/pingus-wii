// src/math/vector2i.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "vector2f.hpp"

#include <ostream>

Vector2i::Vector2i(const Vector2f& v)
  : x(int(v.x)), y(int(v.y))
{}

std::ostream& operator<<(std::ostream& s, const Vector2i& v)
{
  s << "Vector2i(" << v.x << ", " << v.y << ")";
  return s;
}

// EOF
