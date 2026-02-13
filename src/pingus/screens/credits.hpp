// src/pingus/screens/credits.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_SCREENS_CREDITS_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_CREDITS_HPP

#include <memory>
#include <string>
#include <vector>

#include "engine/display/font.hpp"
#include "engine/display/scene_context.hpp"
#include "engine/display/sprite.hpp"
#include "engine/screen/gui_screen.hpp"

namespace pingus {

class Pathname;

class Credits : public GUIScreen
{
private:
  std::unique_ptr<SceneContext> scene_context;

  bool fast_scrolling;
  Sprite background;
  Sprite blackboard;
  Sprite pingu;

  Font    font;
  Font    font_small;

  bool is_init;

  float end_offset;
  float offset;

  struct CreditLine
  {
    std::string text;
    Font font;
    float relative_y;
  };

  /** Pre-calculated list of lines to display */
  std::vector<CreditLine> credits;

public:
  Credits(const Pathname& filename);
  virtual ~Credits();

  void update(float);
  void draw_background(DrawingContext& gc);

  void on_startup();

  void on_pause_press();
  void on_fast_forward_press();
  void on_escape_press();

private:
  Credits(const Credits&);
  Credits& operator=(const Credits&);

};


} // namespace pingus
#endif

// EOF
