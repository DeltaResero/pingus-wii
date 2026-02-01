// src/editor/file_list.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_FILE_LIST_HPP
#define HEADER_PINGUS_EDITOR_FILE_LIST_HPP

#include <functional>

#include "engine/display/sprite.hpp"
#include "engine/gui/rect_component.hpp"
#include "util/system.hpp"

namespace pingus::editor {

class FileList : public gui::RectComponent
{
private:
  int hspace;
  int vspace;

  Sprite file_icon;
  Sprite directory_icon;
  std::string m_direction;
  System::Directory directory;
  int current_item;
  int click_item;
  int page;
  int num_pages;

public:
  FileList(const Rect& rect);

  void draw (DrawingContext& gc);
  void update (float delta);

  void update_layout();
  std::string get_direction() const { return m_direction; }
  void set_directory(const std::string& pathname, const std::string& pattern = "*");

  void on_pointer_move (int x, int y);

  void on_primary_button_press (int x, int y);
  void on_primary_button_release (int x, int y);

  void next_page();
  void prev_page();

  bool has_more_next_pages();
  bool has_more_prev_pages();

  std::function<void (const System::DirectoryEntry&)> on_click;

private:
  int items_per_page();

  FileList (const FileList&);
  FileList& operator= (const FileList&);
};

} // namespace pingus::editor

#endif

// EOF
