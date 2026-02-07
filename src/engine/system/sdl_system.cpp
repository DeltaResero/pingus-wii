// src/engine/system/sdl_system.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/system/sdl_system.hpp"

#include <SDL_image.h>

#ifdef __WII__
#  include <wiiuse/wpad.h>
#endif

#include "engine/display/display.hpp"
#include "math/size.hpp"
#include "util/pathname.hpp"
#include "util/log.hpp"

namespace pingus {


SDLSystem::SDLSystem()
{
#ifdef __WII__
  // Initialize WPAD before SDL on Wii
  WPAD_Init();
  WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);
  WPAD_SetVRes(WPAD_CHAN_ALL, 640, 480);

  log_info("Wii Remote initialized");

  // Initialize SDL with joystick support (required for Wii Remote input)
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) != 0)
#else
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
#endif
  {
    log_error("Unable to initialize SDL: {}", SDL_GetError());
    exit(1);
  }
  else
  {
    atexit(SDL_Quit);
  }

#ifdef __WII__
  // Open joystick 0 to receive Wii Remote events
  SDL_JoystickEventState(SDL_ENABLE);
  int num_joysticks = SDL_NumJoysticks();
  log_info("SDL detected {} joystick(s)", num_joysticks);

  if (num_joysticks > 0)
  {
    SDL_Joystick* joy = SDL_JoystickOpen(0);
    if (!joy)
    {
      log_warn("Could not open Wii Remote joystick 0: {}", SDL_GetError());
    }
    else
    {
      log_info("Wii Remote joystick opened: {} axes, {} buttons",
               SDL_JoystickNumAxes(joy),
               SDL_JoystickNumButtons(joy));
    }
  }
  else
  {
    log_warn("No Wii Remotes detected by SDL");
  }
#endif
}

SDLSystem::~SDLSystem()
{
}

void
SDLSystem::create_window(FramebufferType framebuffer_type, const Size& size, bool fullscreen, bool resizable)
{
  SDL_WM_SetCaption("Pingus " VERSION, "Pingus " VERSION);
  SDL_WM_SetIcon(IMG_Load(Pathname("images/icons/pingus.png", Pathname::DATA_PATH).get_sys_path().c_str()), 0);

  Display::create_window(framebuffer_type, size, fullscreen, resizable);

  SDL_EnableUNICODE(1);

  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}


} // namespace pingus

// EOF
