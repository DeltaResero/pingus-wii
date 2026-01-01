// src/pingus/screens/story_screen.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_SCREENS_STORY_SCREEN_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_STORY_SCREEN_HPP

#include <memory>

#include "engine/screen/gui_screen.hpp"
#include "pingus/worldmap/worldmap_story.hpp"

class StoryScreenComponent;

namespace WorldmapNS {
class WorldmapStory;
} // namespace WorldmapNS

namespace GUI {
class SurfaceButton;
}

class StoryScreen : public GUIScreen
{
private:
  std::unique_ptr<WorldmapNS::WorldmapStory> story;
  StoryScreenComponent* story_comp;
  GUI::SurfaceButton* continue_button;
  GUI::SurfaceButton* skip_button;
  bool m_credits;

public:
  StoryScreen(const FileReader& reader, bool credits = false);
  ~StoryScreen();

  void on_startup();
  void on_fast_forward_press ();
  void on_escape_press ();

  void resize(const Size& size);

private:
  StoryScreen (const StoryScreen&);
  StoryScreen& operator= (const StoryScreen&);
};

#endif

// EOF
