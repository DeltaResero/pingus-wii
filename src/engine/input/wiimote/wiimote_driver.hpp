// src/engine/input/wiimote/wiimote_driver.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_INPUT_WIIMOTE_WIIMOTE_DRIVER_HPP
#define HEADER_PINGUS_ENGINE_INPUT_WIIMOTE_WIIMOTE_DRIVER_HPP

#include "engine/input/driver.hpp"

namespace Input {

class WiimoteDriver : public Driver
{
private:
  struct ButtonBinding {
    Button* binding;
    int button;
  };

  struct AxisBinding {
    Axis* binding;
    int axis;
  };

  std::vector<ButtonBinding> button_bindings;
  std::vector<AxisBinding>   axis_bindings;

public:
  WiimoteDriver();
  ~WiimoteDriver();

  void update(float delta);

  std::string get_name() const { return "wiimote"; }

  Button*   create_button  (const FileReader& reader, Control* parent);
  Axis*     create_axis    (const FileReader& reader, Control* parent);
  Scroller* create_scroller(const FileReader& reader, Control* parent);
  Pointer*  create_pointer (const FileReader& reader, Control* parent);
  Keyboard* create_keyboard(const FileReader& reader, Control* parent) { return 0; }
};

} // namespace Input

#endif

// EOF
