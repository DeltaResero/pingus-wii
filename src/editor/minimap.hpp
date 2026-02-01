// src/editor/minimap.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_MINIMAP_HPP
#define HEADER_PINGUS_EDITOR_MINIMAP_HPP

#include <memory>

#include "engine/gui/rect_component.hpp"

namespace pingus::editor {

class EditorScreen;

class Minimap : public GUI::RectComponent
{
private:
  EditorScreen* editor;
  std::unique_ptr<DrawingContext> drawing_context;
  bool dragging;

public:
  Minimap(EditorScreen*, const Rect& );
  ~Minimap();

  void draw (DrawingContext& gc);
  void update (float delta);

  void on_primary_button_press (int x, int y);
  void on_primary_button_release (int x, int y);
  void on_pointer_move(int x, int y);

  void update_layout();

private:
  Minimap(const Minimap&);
  Minimap & operator=(const Minimap&);
};

} // namespace pingus::editor

#endif

// EOF
