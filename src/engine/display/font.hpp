// src/engine/display/font.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_DISPLAY_FONT_HPP
#define HEADER_PINGUS_ENGINE_DISPLAY_FONT_HPP

#include <cstdint>
#include <memory>

#include "math/rect.hpp"

class FontImpl;
class FontDescription;
class Framebuffer;

class Font
{
public:
  Font();
  Font(const FontDescription& desc);

  void render(int x, int y, const std::string& text, Framebuffer& fb);
  void render(Origin origin, int x, int y, const std::string& text, Framebuffer& fb);

  int  get_height() const;
  float get_width(uint32_t unicode) const;
  float get_width(const std::string& text) const;
  Size get_size(const std::string& text) const;
  Rect bounding_rect(int , int, const std::string& str) const;

private:
  std::shared_ptr<FontImpl> impl;
};

#endif

// EOF
