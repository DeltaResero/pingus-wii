// src/engine/gui/combobox_listener.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2006 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_GUI_COMBOBOX_LISTENER_HPP
#define HEADER_PINGUS_ENGINE_GUI_COMBOBOX_LISTENER_HPP

namespace pingus::gui {

class Combobox;

class ComboboxListener {
public:
  virtual void combobox_changed(Combobox* box) = 0;
  virtual ~ComboboxListener() { }
};      // ComboboxListener class

}       // GUI namespace

#endif

// EOF
