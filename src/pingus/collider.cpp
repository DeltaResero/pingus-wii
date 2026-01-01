// src/pingus/collider.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/collider.hpp"

#include "math/vector3f.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/world.hpp"

Collider::Collider()
{
}

Collider::~Collider()
{
}

bool Collider::operator() (World* const world, Vector3f current_pos,
                           const Vector3f& step_vector) const
{
  return false;
}

int Collider::getpixel(World* const world, const Vector3f& pos) const
{
  return world->get_colmap()->getpixel(static_cast<int>(pos.x),
                                       static_cast<int>(pos.y));
}

// EOF
