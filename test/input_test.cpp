// test/input_test.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include <SDL.h>
#include <iostream>
#include <stdexcept>

#include "engine/input/controller.hpp"
#include "engine/input/manager.hpp"
#include "util/pathname.hpp"

int main()
{
  try
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
      std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;
      exit(1);
    }
    atexit(SDL_Quit);

    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, 0);

    pingus::input::Manager manager;

    pingus::input::ControllerPtr controller =
        manager.create_controller(pingus::Pathname(
            "../data/controller/input2.scm", pingus::Pathname::SYSTEM_PATH));

    while (true)
    {
      std::vector<pingus::input::Event> events;

      controller->poll_events(events);

      for (std::vector<pingus::input::Event>::iterator i = events.begin();
           i != events.end(); ++i)
      {
        // insert code here
      }

      manager.update(0.033f);

      SDL_Flip(screen);
    }
  }
  catch (std::exception &err)
  {
    std::cout << "Exception: " << err.what() << std::endl;
  }

  return 0;
}

// EOF
