// src/engine/input/xinput/xinput_driver.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_INPUT_XINPUT_XINPUT_DRIVER_HPP
#define HEADER_PINGUS_ENGINE_INPUT_XINPUT_XINPUT_DRIVER_HPP

#include <X11/extensions/XInput.h>

#include <SDL_syswm.h>

#include "engine/input/driver.hpp"

namespace Input {

class XInputDevice;

class XInputDriver : public Driver
{
private:
  SDL_SysWMinfo sys;
  std::vector<XInputDevice*> devices;

private:
  void setup_xinput();
  Bool xinput_is_present();

  XDeviceInfo* find_device_info(Display *display,
                                const char* name,
                                Bool only_extended);
public:
  XInputDriver();
  ~XInputDriver();

  SDL_SysWMinfo& get_syswminfo() { return sys; }

  std::string get_name() const { return "xinput"; }
  void update(float delta);

  Button*   create_button  (const FileReader& reader, Control* parent);
  Axis*     create_axis    (const FileReader& reader, Control* parent);
  Scroller* create_scroller(const FileReader& reader, Control* parent);
  Pointer*  create_pointer (const FileReader& reader, Control* parent);
  Keyboard* create_keyboard(const FileReader& reader, Control* parent) { return 0; }
};

} // namespace Input

#endif

// EOF
