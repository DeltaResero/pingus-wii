// src/pingus/direction.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/direction.hpp"

Direction::Direction() : direction(NONE)
{
}

Direction::Direction(const Direction& dir) :
  direction(dir.direction)
{
}

Direction::~Direction()
{
  // do nothing
}

Direction&
Direction::operator=(const Direction& dir)
{
  if (this != &dir) {
    direction = dir.direction;
  }
  return *this;
}

void
Direction::change()
{
  if (direction == LEFT)
    direction = RIGHT;
  else
    direction = LEFT;
}

void
Direction::left()
{
  direction = LEFT;
}

void
Direction::right()
{
  direction = RIGHT;
}

bool
Direction::is_left() const
{
  return (direction == LEFT);
}

bool
Direction::is_right() const
{
  return direction == RIGHT;
}

// EOF
