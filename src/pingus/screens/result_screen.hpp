// src/pingus/screens/result_screen.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_SCREENS_RESULT_SCREEN_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_RESULT_SCREEN_HPP

#include "engine/screen/gui_screen.hpp"
#include "pingus/result.hpp"

namespace pingus::gui {
class SurfaceButton;
} // namespace pingus::gui

class ResultScreen : public GUIScreen
{
private:
  Result result;
  pingus::gui::SurfaceButton*   ok_button;
  pingus::gui::SurfaceButton* abort_button;
  pingus::gui::SurfaceButton* retry_button;

public:
  ResultScreen(Result result);
  void on_startup();

  void on_pause_press();
  void on_fast_forward_press();
  void on_escape_press();

  void retry_level();
  void close_screen();

  void resize(const Size&);
private:
  ResultScreen (const ResultScreen&);
  ResultScreen& operator= (const ResultScreen&);
};

#endif

// EOF
