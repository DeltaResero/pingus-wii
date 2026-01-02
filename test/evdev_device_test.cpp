// test/evdev_device_test.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/input/evdev/evdev_device.hpp"

// g++ -D__TEST__ evdev_device.cpp -o evdev -Wall -Werror

#include <iostream>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "Usage: evdev FILENAME" << std::endl;
  }
  else
  {
    std::cout << "EvdevDevice: " << argv[1] << std::endl;

    Input::EvdevDevice dev(argv[1]);
    while(true)
    {
      dev.update(0.0f);
    }
  }
  return 0;
}

// EOF
