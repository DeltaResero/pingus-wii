// src/pingus/screens/addon_menu.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_SCREENS_ADDON_MENU_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_ADDON_MENU_HPP

#include "engine/display/sprite.hpp"
#include "engine/screen/gui_screen.hpp"

namespace pingus {

class AddOnMenu : public GUIScreen
{
private:
  Sprite background;
  Sprite ok_button;

  struct AddOnEntry
  {
    std::string title;
    std::string description;
    std::string author;

    AddOnEntry(const std::string& title_,
               const std::string& description_,
               const std::string& author_)
      : title(title_),
        description(description_),
        author(author_)
    {}
  };

public:
  AddOnMenu();
  ~AddOnMenu();

  void draw_background (DrawingContext& gc);
  void on_escape_press ();

private:
  AddOnMenu (const AddOnMenu&);
  AddOnMenu& operator= (const AddOnMenu&);
};


} // namespace pingus
#endif

// EOF
