// src/engine/input/driver_factory.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "driver_factory.hpp"

#include "engine/input/core_driver.hpp"
#include "engine/input/sdl_driver.hpp"

namespace pingus::input {

std::unique_ptr<Driver>
DriverFactory::create(const std::string& name, Manager* manager)
{
  if (name == "sdl")
  {
    return std::make_unique<SDLDriver>();
  }
  else if (name == "core")
  {
    return std::make_unique<CoreDriver>(manager);
  }
  else
  {
    return nullptr;
  }
}

} // namespace pingus::input

// EOF
