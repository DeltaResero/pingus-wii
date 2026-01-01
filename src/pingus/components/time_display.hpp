// src/pingus/components/time_display.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_TIME_DISPLAY_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_TIME_DISPLAY_HPP

#include "engine/display/font.hpp"
#include "engine/display/sprite.hpp"
#include "engine/gui/component.hpp"

class Font;
class Server;
class GameSession;
class DrawingContext;

class TimeDisplay : public GUI::Component
{
private:
  Server*   server;
  Font   font;
  Sprite infinity_symbol;

public:
  TimeDisplay(GameSession* c);
  virtual ~TimeDisplay() {}

  void draw(DrawingContext& gc);

private:
  TimeDisplay (const TimeDisplay&);
  TimeDisplay& operator= (const TimeDisplay&);
};

#endif

// EOF
