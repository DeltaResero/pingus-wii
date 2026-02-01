// src/editor/message_box.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_MESSAGE_BOX_HPP
#define HEADER_PINGUS_EDITOR_MESSAGE_BOX_HPP

#include <functional>

#include "engine/gui/group_component.hpp"
#include "editor/button.hpp"

namespace pingus::editor {

class MessageBox : public GUI::GroupComponent
{
private:
  Button* m_ok_button;
  Button* m_cancel_button;

  std::string m_title;
  std::string m_text;

public:
  MessageBox(const Rect& rect);

  void draw_background(DrawingContext& gc);
  void update_layout();

  void set_title(const std::string& text);
  void set_text(const std::string& text);
  void set_ok_text(const std::string& text);

  void on_ok_button();
  void on_cancel_button();

public:
  std::function<void()> on_ok;

private:
  MessageBox(const MessageBox&);
  MessageBox& operator=(const MessageBox&);
};

} // namespace pingus::editor

#endif

// EOF
