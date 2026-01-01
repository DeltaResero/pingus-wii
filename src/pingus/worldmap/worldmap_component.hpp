// src/pingus/worldmap/worldmap_component.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDMAP_WORLDMAP_COMPONENT_HPP
#define HEADER_PINGUS_PINGUS_WORLDMAP_WORLDMAP_COMPONENT_HPP

#include <memory>

#include "engine/gui/gui_manager.hpp"

class SceneContext;

namespace WorldmapNS {

class WorldmapScreen;
class Worldmap;

class WorldmapComponent : public GUI::Component
{
private:
  std::unique_ptr<SceneContext> scene_context;
  WorldmapScreen* worldmap_screen;
  bool m_fast_forward;

public:
  WorldmapComponent(WorldmapScreen* worldmap_screen);
  ~WorldmapComponent();

  void on_primary_button_press (int x, int y);
  void on_secondary_button_press (int x, int y);
  void on_pointer_move(int x, int y);

  void on_fast_forward_press();
  void on_fast_forward_release();

  void draw (DrawingContext& gc);
  void update (float delta);

  bool is_at (int, int) { return true; }

private:
  WorldmapComponent (const WorldmapComponent&);
  WorldmapComponent& operator= (const WorldmapComponent&);
};

} // namespace WorldmapNS

#endif

// EOF
