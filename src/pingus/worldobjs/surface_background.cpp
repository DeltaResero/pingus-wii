// src/pingus/worldobjs/surface_background.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/surface_background.hpp"

#include <algorithm>

#include "engine/display/scene_context.hpp"
#include "pingus/globals.hpp"
#include "pingus/resource.hpp"
#include "pingus/world.hpp"

namespace pingus::worldobjs {

SurfaceBackground::SurfaceBackground(const FileReader& reader) :
  para_x(0.5),
  para_y(0.5),
  pos(),
  scroll_x(0.0),
  scroll_y(0.0),
  color(0,0,0,0),
  stretch_x(false),
  stretch_y(false),
  keep_aspect(false),
  bg_sprite(),
  tile_size(),
  scroll_ox(0),
  scroll_oy(0)
{
  if (!reader.read_vector("position", pos))
    pos = Vector3f(0.f, 0.f, -150.f);

  ResDescriptor desc;

  reader.read_desc("surface", desc);
  if (!reader.read_colori("colori", color))
  {
    Colorf tmp_colorf;
    if (reader.read_colorf("color", tmp_colorf))
    {
      color = tmp_colorf.to_color();
    }
  }

  reader.read_float("para-x", para_x);
  reader.read_float("para-y", para_y);

  reader.read_float("scroll-x", scroll_x);
  reader.read_float("scroll-y", scroll_y);

  reader.read_bool("stretch-x", stretch_x);
  reader.read_bool("stretch-y", stretch_y);

  reader.read_bool("keep-aspect", keep_aspect);

  if (!stretch_x && !stretch_y && color.a == 0)
  {
    // FIXME: would be nice to allow surface manipulation with
    // animated sprites, but it's not that easy to do
    bg_sprite = Sprite(desc);
    tile_size = Size(bg_sprite.get_width(), bg_sprite.get_height());
  }
  else
  {
    Surface surface = Resource::load_surface(desc);

    if (color.a != 0 && surface.is_indexed())
    {
      if (surface.has_colorkey())
      {
        surface = surface.convert_to_rgba();
      }
      else
      {
        surface = surface.convert_to_rgb();
      }
    }

    surface.fill(color);

    // Stretched at draw time
    tile_size = surface.get_size();
    if (stretch_x && stretch_y)
    {
      tile_size = Size(world->get_width(), world->get_height());
    }
    else if (stretch_x && !stretch_y)
    {
      if (keep_aspect)
      {
        float aspect = static_cast<float>(surface.get_height()) / static_cast<float>(surface.get_width());
        tile_size = Size(world->get_width(), static_cast<int>(static_cast<float>(world->get_width()) * aspect));
      }
      else
      {
        tile_size = Size(world->get_width(), surface.get_height());
      }
    }
    else if (!stretch_x && stretch_y)
    {
      if (keep_aspect)
      {
        float aspect = static_cast<float>(surface.get_width()) / static_cast<float>(surface.get_height());
        tile_size = Size(static_cast<int>(static_cast<float>(world->get_height()) * aspect), world->get_height());
      }
      else
      {
        tile_size = Size(surface.get_width(), world->get_height());
      }
    }

    bg_sprite = Sprite(surface);
  }
}

float
SurfaceBackground::get_z_pos () const
{
  return pos.z;
}

void
SurfaceBackground::update()
{
  bg_sprite.update();

  if (!bg_sprite)
    return;

  if (scroll_x)
  {
    scroll_ox += scroll_x;

    if (scroll_ox > tile_size.width)
      scroll_ox -= static_cast<float>(tile_size.width);
    else if (-scroll_ox > tile_size.width)
      scroll_ox += static_cast<float>(tile_size.width);
  }

  if (scroll_y)
  {
    scroll_oy += scroll_y;

    if (scroll_oy > tile_size.height)
      scroll_oy -= static_cast<float>(tile_size.height);
    else if (-scroll_oy > tile_size.height)
      scroll_oy += static_cast<float>(tile_size.height);
  }
}

void
SurfaceBackground::draw (SceneContext& gc)
{
  if (!bg_sprite)
    return;

  Vector2i offset = gc.color().world_to_screen(Vector2i(0,0));

  offset.x -= gc.color().get_rect().left;
  offset.y -= gc.color().get_rect().top;

  int start_x = static_cast<int>((static_cast<float>(offset.x) * para_x) + scroll_ox);
  int start_y = static_cast<int>((static_cast<float>(offset.y) * para_y) + scroll_oy);

  // Start from the tile that covers the visible area's left and top edges
  start_x %= tile_size.width;
  if (start_x > 0)
    start_x -= tile_size.width;

  start_y %= tile_size.height;
  if (start_y > 0)
    start_y -= tile_size.height;

  const int end_x = std::min(world->get_width(),  gc.color().get_width());
  const int end_y = std::min(world->get_height(), gc.color().get_height());

  const bool stretched = (stretch_x || stretch_y);

  for(int y = start_y; y < end_y; y += tile_size.height)
  {
    for(int x = start_x; x < end_x; x += tile_size.width)
    {
      if (stretched)
        gc.color().draw(bg_sprite, Vector2i(x - offset.x, y - offset.y), tile_size, pos.z);
      else
        gc.color().draw(bg_sprite, Vector2i(x - offset.x, y - offset.y), pos.z);
    }
  }
}

} // namespace pingus::worldobjs

// EOF
