// src/pingus/screens/level_menu.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_SCREENS_LEVEL_MENU_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_LEVEL_MENU_HPP

#include "engine/display/sprite.hpp"
#include "engine/screen/gui_screen.hpp"
#include "pingus/levelset.hpp"

namespace pingus::gui {
class SurfaceButton;
} // namespace pingus::gui

class LevelSelector;
class LevelsetSelector;

class LevelMenu : public GUIScreen
{
private:
  int x_pos;
  int y_pos;

  Sprite background;
  Sprite blackboard;
  Sprite ok_button;

  LevelSelector*    level_selector;
  LevelsetSelector* levelset_selector;

  pingus::gui::SurfaceButton* abort_button;
  pingus::gui::SurfaceButton* next_button;
  pingus::gui::SurfaceButton* prev_button;

public:
  LevelMenu();
  ~LevelMenu();

  void draw_background(DrawingContext& gc);
  void on_escape_press();
  void on_action_up_press();
  void on_action_down_press();

  void set_levelset(Levelset* levelset);

  void next_page();
  void prev_page();

  void resize(const Size& size);

private:
  LevelMenu (const LevelMenu&);
  LevelMenu& operator= (const LevelMenu&);
};

#endif

// EOF
