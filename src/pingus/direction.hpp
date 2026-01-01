// src/pingus/direction.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_DIRECTION_HPP
#define HEADER_PINGUS_PINGUS_DIRECTION_HPP

/// Simple class for managing the direction of a pingu
class Direction
{
public:
  enum Dir { LEFT = -1, NONE = 0, RIGHT = +1 };
private:
  Dir direction;

public:
  Direction ();
  Direction (const Direction& dir);
  ~Direction ();

  Direction& operator= (const Direction&);

  operator int () const { return direction; }

  void change ();
  void left ();
  void right ();

  bool is_left () const;
  bool is_right () const;
};

#endif

// EOF
