// src/pingus/worldmap/worldmap_screen.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldmap/worldmap_screen.hpp"

#include <algorithm>

#include "engine/display/display.hpp"
#include "engine/gui/surface_button.hpp"
#include "engine/screen/screen_manager.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/fonts.hpp"
#include "pingus/res_descriptor.hpp"
#include "pingus/screens/story_screen.hpp"
#include "pingus/worldmap/pingus.hpp"
#include "pingus/worldmap/worldmap.hpp"
#include "pingus/worldmap/worldmap_component.hpp"

namespace pingus::worldmap {

class WorldmapScreenCloseButton
  : public pingus::gui::SurfaceButton
{
private:
  WorldmapScreen* worldmap_screen;

  /** A plain strip of chalkboard, and the same strip upside down */
  Sprite board;
  Sprite board_below;
  Sprite box;
  Sprite box_ticked;

public:
  WorldmapScreenCloseButton(WorldmapScreen* worldmap_screen);
  void on_click();
  void draw (DrawingContext& gc);
  bool is_at (int x, int y);
  void on_pointer_enter();

private:
  WorldmapScreenCloseButton(const WorldmapScreenCloseButton&);
  WorldmapScreenCloseButton & operator=(const WorldmapScreenCloseButton&);
};

namespace {

// The button's face; the board behind it reaches to the screen's corner.
const int LEAVE_WIDTH  = 119;
const int LEAVE_HEIGHT = 37;

// Lines the strip's green up with where the old Leave board's was; its
// frame is thicker and dips toward the right end.
const Vector2i BOARD_OFFSET(2, -5);

} // namespace

WorldmapScreenCloseButton::WorldmapScreenCloseButton(WorldmapScreen* worldmap_screen_) :
  pingus::gui::SurfaceButton(0, Display::get_height() - LEAVE_HEIGHT,
                     "core/worldmap/levelname_bg",
                     "core/worldmap/levelname_bg",
                     "core/worldmap/levelname_bg"),
  worldmap_screen(worldmap_screen_),
  board("core/worldmap/levelname_bg"),
  board_below(ResDescriptor("core/worldmap/levelname_bg", ResourceModifier::ROT180FLIP)),
  box("core/menu/checkbox_small"),
  box_ticked("core/menu/checkbox_marked_small")
{
}

void
WorldmapScreenCloseButton::on_pointer_enter()
{
  SurfaceButton::on_pointer_enter();
  pingus::sound::PingusSound::play_sound ("tick");
}

void
WorldmapScreenCloseButton::draw (DrawingContext& gc)
{
  // The board runs in from off the left edge, and its mirror image fills
  // down to the bottom when TV Overscan lifts the button off it.
  const int board_x = x_pos + LEAVE_WIDTH - board.get_width() + BOARD_OFFSET.x;
  const int board_y = y_pos + BOARD_OFFSET.y;
  gc.draw(board, Vector2i(board_x, board_y));
  if (board_y + board.get_height() < Display::get_height())
    gc.draw(board_below, Vector2i(board_x, board_y + board.get_height()));

  // Shrunk to the size of the box the old Leave board had drawn on it.
  gc.draw(mouse_over ? box_ticked : box, Vector2i(x_pos + 83, y_pos + 9), Size(28, 28));
  gc.print_center(pingus::fonts::chalk_small, Vector2i(x_pos + 44, y_pos + 12), "Leave?");
}

bool
WorldmapScreenCloseButton::is_at (int x, int y)
{
  return x >= 0 && x < x_pos + LEAVE_WIDTH + BOARD_OFFSET.x
    && y > y_pos + BOARD_OFFSET.y && y < Display::get_height();
}

void
WorldmapScreenCloseButton::on_click()
{
  ScreenManager::instance ()->pop_screen ();
}


WorldmapScreen::WorldmapScreen() :
  is_init(false),
  exit_worldmap(false),
  worldmap(),
  new_worldmap(),
  close_button(),
  m_worldmap_component()
{
  // FIXME: a bit ugly because of the proteced member, but should work
  // FIXME: well enough. GUIScreen could also use multi-inheritage,
  // FIXME: but that could lead to member function name conflicts
  m_worldmap_component = gui_manager->create<WorldmapComponent>(this);
  close_button = gui_manager->create<WorldmapScreenCloseButton>(this);
}

WorldmapScreen::~WorldmapScreen ()
{
}

void
WorldmapScreen::load(const Pathname& filename)
{
  worldmap = std::unique_ptr<Worldmap>(new Worldmap(filename));
}

void
WorldmapScreen::on_startup ()
{
  GUIScreen::on_startup();

  // TV Overscan may have changed in Options.
  place_close_button();
  exit_worldmap = false;

  if (worldmap.get())
    worldmap->on_startup ();
}

void
WorldmapScreen::on_escape_press ()
{
  //log_info("WorldmapScreen::on_escape_press ()...");
  exit_worldmap = true;
}

void
WorldmapScreen::update (float delta)
{
  GUIScreen::update(delta);

  // Exit the word
  if (exit_worldmap)
    ScreenManager::instance ()->pop_screen();

  // Check if new worldmap is set and if so, change it
  if (new_worldmap.get())
  {
    worldmap = std::move(new_worldmap);
  }
}

void
WorldmapScreen::draw_foreground(DrawingContext& /*gc*/)
{
}

Rect
WorldmapScreen::get_trans_rect() const
{
  return Rect(Vector2i(std::max((Display::get_width()  - worldmap->get_width())/2,  0),
                       std::max((Display::get_height() - worldmap->get_height())/2, 0)),
              Size(std::min(Display::get_width(),  worldmap->get_width()),
                   std::min(Display::get_height(), worldmap->get_height())));
}

void
WorldmapScreen::show_intro_story()
{
  ScreenManager::instance()->push_screen(std::make_shared<StoryScreen>(worldmap->get_worldmap().get_intro_story()));
}

void
WorldmapScreen::show_end_story()
{
  ScreenManager::instance()->push_screen(std::make_shared<StoryScreen>(worldmap->get_worldmap().get_end_story()));
}

void
WorldmapScreen::resize(const Size& size_)
{
  GUIScreen::resize(size_);
  place_close_button();
}

void
WorldmapScreen::place_close_button()
{
  const Size margin = Display::get_overscan_margin();
  close_button->set_pos(margin.width, size.height - LEAVE_HEIGHT - margin.height);
}

void
WorldmapScreen::on_fast_forward_press()
{
  m_worldmap_component->on_fast_forward_press();
}

void
WorldmapScreen::on_fast_forward_release()
{
  m_worldmap_component->on_fast_forward_release();
}

} // namespace pingus::worldmap

// EOF
