// src/pingus/worldmap/worldmap_story.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDMAP_WORLDMAP_STORY_HPP
#define HEADER_PINGUS_PINGUS_WORLDMAP_WORLDMAP_STORY_HPP

#include <string>
#include <vector>

#include "pingus/res_descriptor.hpp"


class FileReader;

class StoryPage
{
public:
  StoryPage() :
    image(),
    text(),
    page_name()
  {}

  StoryPage(ResDescriptor arg_image, std::string arg_text, std::string arg_name = "")
    : image(arg_image), text(arg_text), page_name(arg_name)
  {}

  ResDescriptor image;
  std::string   text;
  std::string   page_name;
};

namespace WorldmapNS {

class WorldmapStory
{
public:
  WorldmapStory(const FileReader& reader);
  ~WorldmapStory() { }

  std::string get_title() const { return title; }
  std::string get_music() const { return music; }
  std::vector<StoryPage> get_pages() const { return pages; }

private:
  std::string title;
  std::string music;
  std::vector<StoryPage> pages;
};

} // namespace WorldmapNS

#endif

/*EOF*/

// EOF
