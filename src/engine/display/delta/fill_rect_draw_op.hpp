// src/engine/display/delta/fill_rect_draw_op.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_DISPLAY_DELTA_FILL_RECT_DRAW_OP_HPP
#define HEADER_PINGUS_ENGINE_DISPLAY_DELTA_FILL_RECT_DRAW_OP_HPP

struct FillRectDrawOp : public DrawOp
{
  Rect  rect;
  Color color;

  FillRectDrawOp(const Rect& rect_, const Color& color_)
    : DrawOp(FILLRECT_DRAWOP),
      rect(rect_),
      color(color_)
  {
    id = make_id(type, rect.left, rect.top);
  }

  void render(Framebuffer& fb) {
    fb.fill_rect(rect, color);
  }

  void mark_changed_regions(std::vector<Rect>& update_rects) const {
    update_rects.push_back(rect);
  }

  bool operator==(const FillRectDrawOp& rhs) const {
    return
      rect  == rhs.rect &&
      color == rhs.color;
  }
};

#endif

// EOF
