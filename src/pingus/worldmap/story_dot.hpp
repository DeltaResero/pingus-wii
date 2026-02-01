// src/pingus/worldmap/story_dot.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDMAP_STORY_DOT_HPP
#define HEADER_PINGUS_PINGUS_WORLDMAP_STORY_DOT_HPP

#include <string>

#include "engine/display/sprite.hpp"
#include "pingus/worldmap/dot.hpp"

class FileReader;

namespace pingus::worldmap {

class StoryDot : public Dot
{
private:
  Sprite m_story_dot_highlight;
  Sprite m_story_dot;

  std::string m_name;
  std::string m_story;
  bool m_credits;

public:
  StoryDot(const FileReader& reader);

  void draw(DrawingContext& gc);
  void draw_hover(DrawingContext& gc);

  void update(float delta);
  void on_click();

  bool finished() { return true; }
  bool accessible() { return true; }
  void unlock() {}

private:
  StoryDot(const StoryDot&);
  StoryDot& operator=(const StoryDot&);
};

} // namespace pingus::worldmap

#endif

// EOF
