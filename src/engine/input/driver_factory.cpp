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

#ifdef HAVE_CWIID
#  include "engine/input/wiimote/wiimote_driver.hpp"
#endif

namespace Input {

Driver*
DriverFactory::create(const std::string& name, Manager* manager)
{
  if (name == "sdl")
  {
    return new SDLDriver;
  }
  else if (name == "core")
  {
    return new CoreDriver(manager);
  }
#ifdef HAVE_CWIID
  else if (name == "wiimote")
  {
    return new WiimoteDriver();
  }
#endif
  else
  {
    return 0;
  }
}

} // namespace Input

// EOF
