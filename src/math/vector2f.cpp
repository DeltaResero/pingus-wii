// src/math/vector2f.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2004 Matthias Braun <matze@braunis.de
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "math/vector2f.hpp"

#include <ostream>

namespace pingus {


std::ostream& operator<<(std::ostream& s, const Vector2f& v)
{
  s << "Vector2f(" << v.x << ", " << v.y << ")";
  return s;
}


} // namespace pingus

// EOF
