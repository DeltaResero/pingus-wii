// src/engine/display/sprite_description.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_DISPLAY_SPRITE_DESCRIPTION_HPP
#define HEADER_PINGUS_ENGINE_DISPLAY_SPRITE_DESCRIPTION_HPP

#include <memory>

#include "math/origin.hpp"
#include "math/size.hpp"
#include "math/vector2i.hpp"
#include "util/file_reader.hpp"
#include "util/log.hpp"
#include "util/pathname.hpp"

class SpriteDescription;

typedef std::shared_ptr<SpriteDescription> SpriteDescriptionPtr;

class SpriteDescription
{
public:
  static SpriteDescriptionPtr from_file(const Pathname& path);

public:
  Pathname    filename;
  Vector2i    offset;
  Origin      origin;

  bool        loop;
  int         speed;
  Size        array;
  Vector2i    frame_pos;
  Size        frame_size;

public:
  SpriteDescription() :
    filename(),
    offset(),
    origin(origin_top_left),
    loop(true),
    speed(100),
    array(1, 1),
    frame_pos(),
    frame_size(-1, -1)
  {}

  ~SpriteDescription()
  {
  }
};

#endif

// EOF
