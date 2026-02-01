// src/engine/input/driver.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_INPUT_DRIVER_HPP
#define HEADER_PINGUS_ENGINE_INPUT_DRIVER_HPP

#include <memory>
#include "engine/input/control.hpp"
#include "util/file_reader.hpp"

namespace pingus::input {

class Driver
{
public:
  Driver() {}
  virtual ~Driver() {}

  virtual std::string get_name() const =0;
  virtual void update(float delta) =0;

  virtual std::unique_ptr<Button>   create_button  (const FileReader& reader, Control* parent) =0;
  virtual std::unique_ptr<Axis>     create_axis    (const FileReader& reader, Control* parent) =0;
  virtual std::unique_ptr<Scroller> create_scroller(const FileReader& reader, Control* parent) =0;
  virtual std::unique_ptr<Pointer>  create_pointer (const FileReader& reader, Control* parent) =0;
  virtual std::unique_ptr<Keyboard> create_keyboard(const FileReader& reader, Control* parent) =0;
};

} // namespace pingus::input

#endif

// EOF
