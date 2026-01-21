// src/engine/input/core_driver.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_INPUT_CORE_DRIVER_HPP
#define HEADER_PINGUS_ENGINE_INPUT_CORE_DRIVER_HPP

#include <memory>
#include "engine/input/driver.hpp"

namespace Input {

class Manager;

class CoreDriver : public Driver
{
private:
  Manager* manager;

public:
  CoreDriver(Manager* manager_) : manager(manager_) {}
  virtual ~CoreDriver() {}

  std::string get_name() const { return "core"; }
  void update(float /*delta*/) {}

  std::unique_ptr<Button>   create_button  (const FileReader& reader, Control* parent);
  std::unique_ptr<Axis>     create_axis    (const FileReader& reader, Control* parent);
  std::unique_ptr<Scroller> create_scroller(const FileReader& reader, Control* parent);
  std::unique_ptr<Pointer>  create_pointer (const FileReader& reader, Control* parent);
  std::unique_ptr<Keyboard> create_keyboard(const FileReader& reader, Control* parent);

private:
  CoreDriver(const CoreDriver&);
  CoreDriver & operator=(const CoreDriver&);
};

} // namespace Input

#endif

// EOF
