// src/pingus/components/pingus_counter.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_PINGUS_COUNTER_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_PINGUS_COUNTER_HPP

#include "engine/display/font.hpp"
#include "engine/display/sprite.hpp"
#include "engine/gui/component.hpp"

namespace pingus {

class DrawingContext;
class World;
class Server;

class PingusCounter : public gui::Component
{
private:
  Server* server;
  Font font;
  Sprite background;

public:
  PingusCounter(Server* s);
  virtual ~PingusCounter() {}

  void draw(DrawingContext& gc);
private:
  PingusCounter (const PingusCounter&);
  PingusCounter& operator= (const PingusCounter&);
};


} // namespace pingus
#endif

// EOF
