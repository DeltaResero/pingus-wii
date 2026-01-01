// src/pingus/screens/start_screen.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_SCREENS_START_SCREEN_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_START_SCREEN_HPP

#include "engine/screen/gui_screen.hpp"
#include "pingus/pingus_level.hpp"

namespace GUI {
class SurfaceButton;
} // namespace GUI

class StartScreen : public GUIScreen
{
private:
  PingusLevel plf;
  GUI::SurfaceButton* abort_button;
  GUI::SurfaceButton* ok_button;

public:
  StartScreen(const PingusLevel& plf);
  ~StartScreen();

  void start_game();
  void cancel_game();

  void on_pause_press();
  void on_fast_forward_press();
  void on_escape_press();

  void resize(const Size&);

private:
  StartScreen (const StartScreen&);
  StartScreen& operator= (const StartScreen&);
};

#endif

// EOF
