// src/engine/display/font_description.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_DISPLAY_FONT_DESCRIPTION_HPP
#define HEADER_PINGUS_ENGINE_DISPLAY_FONT_DESCRIPTION_HPP

#include <cstdint>
#include <vector>

#include "math/rect.hpp"
#include "util/pathname.hpp"

class FileReader;

class GlyphDescription
{
public:
  int      image;
  uint32_t unicode;
  Vector2i offset;
  int      advance;
  Rect     rect;

  GlyphDescription();
  GlyphDescription(const FileReader& reader);
};

class GlyphImageDescription
{
public:
  /** Image file from which the basic surface is loaded */
  Pathname pathname;

  /** Characters in the font image */
  std::vector<GlyphDescription> glyphs;

  GlyphImageDescription() :
    pathname(),
    glyphs()
  {}
};

class FontDescription
{
public:
  Pathname    pathname;

  /** Space between two characters, given in pixel */
  float char_spacing;

  /** Spacing between lines, given in multiples of \a size */
  float vertical_spacing;

  /** Vertical height of the font */
  int size;

  std::vector<GlyphImageDescription> images;

  FontDescription(const Pathname& filename);
};

#endif

// EOF
