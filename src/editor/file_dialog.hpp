// src/editor/file_dialog.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_FILE_DIALOG_HPP
#define HEADER_PINGUS_EDITOR_FILE_DIALOG_HPP

#include "editor/file_list.hpp"
#include "engine/gui/group_component.hpp"

namespace pingus::editor {

class Button;
class EditorScreen;
class Inputbox;
class Label;

class FileDialog : public GUI::GroupComponent
{
public:
  enum Mode { LOAD, SAVE };
private:
  EditorScreen* editor;
  Mode mode;

  FileList* file_list;
  Button* up_button;
  Button* down_button;
  Button* open_button;
  Button* cancel_button;

  Button* datadir_button;
  Button* userdir_button;

  Label* pathname_label;
  Label* filename_label;

  Inputbox* pathname_inputbox;
  Inputbox* filename_inputbox;

public:
  FileDialog(EditorScreen* editor, const Rect& rect, Mode mode);
  ~FileDialog();

  void draw_background(DrawingContext& gc);
  void update_layout();

  void load_file(const System::DirectoryEntry& entry);
  void set_directory(const std::string& pathname);

private:
  void on_cancel();
  void on_open();

  void on_up();
  void on_down();

  void on_datadir();
  void on_userdir();

  void on_filename_enter();
  void on_pathname_change();

private:
  void update_button_state();

  FileDialog (const FileDialog&);
  FileDialog& operator= (const FileDialog&);
};

} // namespace pingus::editor

#endif

// EOF
