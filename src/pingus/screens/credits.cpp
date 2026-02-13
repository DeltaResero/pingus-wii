// src/pingus/screens/credits.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/screens/credits.hpp"

#include <fstream>
#include <sstream>

#include "engine/display/display.hpp"
#include "engine/gui/gui_manager.hpp"
#include "engine/gui/surface_button.hpp"
#include "engine/screen/screen_manager.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/fonts.hpp"
#include "pingus/stat_manager.hpp"
#include "util/log.hpp"
#include "util/pathname.hpp"

namespace pingus {


class CreditsOkButton
  : public gui::SurfaceButton
{
private:
  Credits* parent;
public:
  CreditsOkButton(Credits* p)
    : gui::SurfaceButton(Display::get_width()/2  + 260,
                         Display::get_height()/2 + 170,
                         "core/start/ok",
                         "core/start/ok_clicked",
                         "core/start/ok_hover"),
      parent(p)
  {
  }

  void on_pointer_enter ()
  {
    SurfaceButton::on_pointer_enter();
    sound::PingusSound::play_sound("tick");
  }

  void on_click() {
    parent->on_escape_press();
    sound::PingusSound::play_sound("yipee");
  }

private:
  CreditsOkButton(const CreditsOkButton&);
  CreditsOkButton & operator=(const CreditsOkButton&);
};

Credits::Credits(const Pathname& filename) :
  scene_context(),
  fast_scrolling(false),
  background("core/menu/wood"),
  blackboard("core/menu/blackboard"),
  pingu("core/misc/creditpingu"),
  font(),
  font_small(),
  is_init(),
  end_offset(),
  offset(),
  credits()
{
  scene_context.reset(new SceneContext);
  fast_scrolling = false;
  gui_manager->create<CreditsOkButton>(this);

  font       = fonts::chalk_normal;
  font_small = fonts::chalk_large;

  std::vector<std::string> raw_lines;

  { // read credit information from filename
    std::ifstream in(filename.get_sys_path());
    if (!in)
    {
      log_error("couldn't open {}", filename.str());

      std::ostringstream out;
      out << "couldn't open " << filename;
      raw_lines.push_back(out.str());
    }
    else
    {
      std::string line;
      while(std::getline(in, line))
      {
        raw_lines.push_back(line);
      }
    }
  }

  // Pre-calculate layout
  end_offset = -static_cast<float>(Display::get_height())/2 - 50; // screen height + grace time
  float current_y = 0;

  for (const std::string& line : raw_lines)
  {
    if (line.empty()) continue;

    switch (line[0])
    {
      case '-':
        credits.push_back({line.substr(1), font, current_y});
        current_y += static_cast<float>(font.get_height() + 5);
        end_offset += static_cast<float>(font.get_height() + 5);
        break;
      case '_':
        credits.push_back({line.substr(1), font_small, current_y});
        current_y += static_cast<float>(font_small.get_height() + 5);
        end_offset += static_cast<float>(font_small.get_height() + 5);
        break;
      case 'n':
        current_y += 50;
        end_offset += 50;
        break;
      default:
        log_error("Credits: Syntax error: Unknown format: '{}'", line[0]);
        break;
    }
  }
  end_offset = -end_offset;
}

Credits::~Credits ()
{
  StatManager::instance()->set_bool("credits-seen", true);
}

void
Credits::update (float delta)
{
  if (offset < end_offset)
  {
    //ScreenManager::instance()->pop_screen ();
  }
  else
  {
    if (fast_scrolling)
      offset -= 450.0f * delta;
    else
      offset -= 35.0f * delta;
  }
}

void
Credits::draw_background (DrawingContext& gc)
{
  {
    // Paint the background wood panel
    for(int y = 0; y < gc.get_height(); y += background.get_height())
      for(int x = 0; x < gc.get_width(); x += background.get_width())
        gc.draw(background, Vector2i(x, y));
  }

  int x = Display::get_width()/2;
  int y = static_cast<int>(offset);

  gc.draw(blackboard, Vector2i(gc.get_width()/2, gc.get_height()/2));
  gc.draw(pingu, Vector2i(gc.get_width()/2, gc.get_height()/2 - 20));

  scene_context->clear();
  scene_context->set_cliprect(Rect(gc.get_width()/2 - 685/2, gc.get_height()/2 - 250,
                                   gc.get_width()/2 + 685/2, gc.get_height()/2 + 250));

  // Only draw lines that are potentially visible
  // Note: Since we use a scene_context, we might still need to push them all,
  // but simple culling could be added here if the list is huge.
  // For now, iterating the pre-calculated vector is fast enough.
  for (const auto& line : credits)
  {
    scene_context->color().print_center(line.font, Vector2i(x, y + static_cast<int>(line.relative_y)), line.text);
  }

  gc.draw(new SceneContextDrawingRequest(scene_context.get(), Vector2i(0,0), 100));
}

void
Credits::on_startup ()
{
  offset = static_cast<float>(Display::get_height()) - 50;
  //PingusSound::play_music("pingus-5.it");
}

void
Credits::on_pause_press ()
{
}

void
Credits::on_fast_forward_press ()
{
  fast_scrolling = ! fast_scrolling;
}

void
Credits::on_escape_press ()
{
  bool credits_seen = false;
  StatManager::instance()->get_bool("credits-seen", credits_seen);
  if (!credits_seen)
  {
    ScreenManager::instance ()->pop_screen ();
  }
  ScreenManager::instance ()->pop_screen ();
}


} // namespace pingus

// EOF
