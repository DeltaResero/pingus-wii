// src/pingus/smallmap_image.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_SMALLMAP_IMAGE_HPP
#define HEADER_PINGUS_PINGUS_SMALLMAP_IMAGE_HPP

#include "engine/display/sprite.hpp"
#include "engine/display/surface.hpp"

class Server;

/** The base image of the small map, it doesn't handle any userinput,
    it only generates the surface */
class SmallMapImage
{
private:
  Server* server;

  /** The canvas that represents the small-colmap */
  Surface canvas;

  /** Graphic surface for the generated rectanglar background of the small map */
  Sprite sur;

  /** number of seconds till the smallmap will update itself */
  float update_count;

  /** The serial is used to track changes to the colmap */
  unsigned int colmap_serial;

public:
  SmallMapImage (Server* s, int width, int height);
  void update (float delta);

  Sprite get_surface();

  /** Regenerate the smallmap surface */
  void update_surface();

private:
  SmallMapImage (const SmallMapImage&);
  SmallMapImage& operator= (const SmallMapImage&);
};

#endif

// EOF
