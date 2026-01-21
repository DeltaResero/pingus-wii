// src/engine/input/manager.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_INPUT_MANAGER_HPP
#define HEADER_PINGUS_ENGINE_INPUT_MANAGER_HPP

#include <memory>
#include <vector>

#include "engine/input/controller_description.hpp"
#include "engine/input/driver.hpp"

namespace Input {

class Manager
{
private:
  typedef std::vector<std::unique_ptr<Driver>> Drivers;
  Drivers drivers;

  std::vector<ControllerPtr> controllers;
  ControllerDescription desc;

public:
  Manager();
  ~Manager();

  /** Resents events for the current controller state */
  void refresh();

  void update(float delta);

  ControllerPtr create_controller(const Pathname& filename);

  std::unique_ptr<Button>   create_button  (const FileReader& reader, Control* parent);
  std::unique_ptr<Axis>     create_axis    (const FileReader& reader, Control* parent);
  std::unique_ptr<Pointer>  create_pointer (const FileReader& reader, Control* parent);
  std::unique_ptr<Scroller> create_scroller(const FileReader& reader, Control* parent);
  std::unique_ptr<Keyboard> create_keyboard(const FileReader& reader, Control* parent);

private:
  Driver* load_driver(const std::string& name);
  Driver* get_driver(const std::string& name);
};

} // namespace Input

#endif

// EOF
