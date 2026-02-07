// src/pingus/collision_map.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_COLLISION_MAP_HPP
#define HEADER_PINGUS_PINGUS_COLLISION_MAP_HPP

#include <cstdint>
#include <memory>

#include "engine/display/sprite.hpp"
#include "pingus/groundtype.hpp"

namespace pingus {

class CollisionMask;

class DrawingContext;
class ResDescriptor;
class PixelStatus;

/** The CollisionMap is used to represent the enviroment where the
    Pingus walk around. The ground can have different properties, it
    can contain lava or water, it can be solid and many more. */
class CollisionMap
{
private:
  /** The serial number indicates the state of the colmap, on every
      change of the colmap it will get increased. */
  unsigned int serial;

  /** The width of the collision map. */
  const int width;

  /** The height of the collision map. */
  const int height;

  /** A array of uchar, each uchar represents a pixel on the map. */
  std::unique_ptr<uint8_t[]> colmap;

  Sprite m_colmap_sprite;
  unsigned int m_colmap_sprite_serial;

public:
  /** Init the colmap from a given area of memory.
      The memory will be deleted in the destructor. */
  CollisionMap(int w, int h);

  /** delete[] the uchar array used for the colmap */
  ~CollisionMap();

  /** Returns the raw uchar array used for the inner representation of
      the colmap. This is used by the smallmap to create the radar  */
  unsigned char* get_data();

  /** Returns the height of the collision map. */
  int get_height();

  /** Returns the width of the collision map. */
  int get_width();

  /** Get pixel value with bounds checking. Returns GP_OUTOFSCREEN if out of bounds.
      Optimized with unsigned cast trick for single comparison per axis. */
  __attribute__((always_inline))
  inline int getpixel(int x, int y) const
  {
    // Unsigned cast trick: if x or y is negative, it becomes a very large unsigned value
    // This allows us to check both lower and upper bounds with just two comparisons
    if (static_cast<unsigned int>(x) < static_cast<unsigned int>(width) &&
        static_cast<unsigned int>(y) < static_cast<unsigned int>(height))
    {
      return colmap[x + y * width];
    }
    else
    {
      return Groundtype::GP_OUTOFSCREEN;
    }
  }

  /** Same as getpixel() but without the range check.
      WARNING: Caller must ensure x and y are within bounds! */
  __attribute__((always_inline))
  inline int getpixel_fast(int x, int y) const
  {
    return colmap[x + y * width];
  }

  /** @return a number which represents the state of the collision
      map, once it changes the serial changes also */
  unsigned get_serial();

  /** Return true if the given GroundType i*/
  bool blit_allowed (int x, int y,  Groundtype::GPType);

  void put(int x, int y, Groundtype::GPType p = Groundtype::GP_GROUND);
  void put(const CollisionMask& mask, int x, int y, Groundtype::GPType);

  void remove(int x, int y);
  void remove(const CollisionMask& mask, int x, int y);

  void draw(DrawingContext& gc);

private:
  CollisionMap (const CollisionMap&);
  CollisionMap& operator= (const CollisionMap&);
};


} // namespace pingus
#endif

// EOF
