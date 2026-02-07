// src/math/vector3f.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "math/vector3f.hpp"

#include <ostream>

namespace pingus {


Vector3f
Vector3f::rotate (float angle, const Vector3f& pos) const
{
  const float s = Math::sin(angle);
  const float c = Math::cos(angle);

  return Vector3f(x * (pos.x * pos.x * (1-c) + c)
                  + y * (pos.x * pos.y * (1-c) - pos.z *s)
                  + z * (pos.x * pos.z * (1-c) + pos.y *s),

                  x * (pos.y * pos.x * (1-c) + pos.z *s)
                  + y * (pos.y * pos.y * (1-c) + c)
                  + z * (pos.y * pos.z * (1-c) - pos.x *s),

                  x * (pos.x * pos.z * (1-c) - pos.y *s)
                  + y * (pos.y * pos.z * (1-c) + pos.x *s)
                  + z * (pos.z * pos.z * (1-c) + c)
    );
}

std::ostream& operator<<(std::ostream& os, const Vector3f& v)
{
  return os << "Vector3f(" << v.x << ", " << v.y << ", " << v.z << ")";
}


} // namespace pingus

// EOF
