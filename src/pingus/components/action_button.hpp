// src/pingus/components/action_button.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_ACTION_BUTTON_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_ACTION_BUTTON_HPP

#include "engine/gui/rect_component.hpp"
#include "pingus/state_sprite.hpp"

namespace pingus {

class Server;
class GameSession;
class ActionHolder;
class Vector;

/** ArmageddonButton, press it to start the armageddon and to turn all
    pingus into bomber

    \sa Client */
class ArmageddonButton : public gui::RectComponent
{
private:
  Server* server;
  bool   pressed;
  float  press_time;
  Sprite sprite;
  Sprite background;
  Sprite backgroundhl;

public:
  ArmageddonButton(Server*, int x, int y);
  virtual ~ArmageddonButton();

  void draw(DrawingContext& gc);
  void update(float);
  void on_primary_button_click (int x, int y);

private:
  ArmageddonButton (const ArmageddonButton&);
  ArmageddonButton& operator= (const ArmageddonButton&);
};

/** Fast Forward button, press it to let the game run faster, press it
    again to return to normal speed

    \sa Client */
class ForwardButton : public gui::RectComponent
{
private:
  GameSession* session;
  Sprite surface;
  Sprite background;
  Sprite backgroundhl;

public:
  ForwardButton(GameSession*, int x, int y);
  virtual ~ForwardButton();

  void draw(DrawingContext& gc);
  void on_primary_button_press (int x, int y);
  void on_primary_button_release (int x, int y);

private:
  ForwardButton (const ForwardButton&);
  ForwardButton& operator= (const ForwardButton&);
};

/** Pause button, press it to pause the game, press it again to
    continue

    \sa Client */
class PauseButton : public gui::RectComponent
{
private:
  GameSession* session;

  Sprite surface;
  Sprite background;
  Sprite backgroundhl;

public:
  PauseButton(GameSession*, int x, int y);
  virtual ~PauseButton();

  void draw(DrawingContext& gc);

  void on_primary_button_click (int x, int y);

private:
  PauseButton (const PauseButton&);
  PauseButton& operator= (const PauseButton&);
};


} // namespace pingus
#endif /* ACTIONBUTTON */

// EOF
