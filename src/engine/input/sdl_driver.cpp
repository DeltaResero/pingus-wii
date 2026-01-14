// src/engine/input/sdl_driver.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/input/sdl_driver.hpp"

#include <cmath>
#include "engine/display/display.hpp"
#include "engine/screen/screen_manager.hpp"
#include "pingus/global_event.hpp"

namespace Input {

SDLDriver::SDLDriver() :
  scroller_bindings(),
  pointer_bindings(),
  keyboard_button_bindings(),
  mouse_button_bindings(),
  joystick_button_bindings(),
  joystick_hat_bindings(),
  joystick_axis_bindings(),
  keyboard_binding(0),
  string2key(),
  joystick_handles(),
  virtual_mouse_x(Display::get_width() / 2.0f),
  virtual_mouse_y(Display::get_height() / 2.0f),
  joy_axis_x(0.0f),
  joy_axis_y(0.0f)
{
  for (int i = 0; i < SDLK_LAST; ++i)
  {
    char* key_name = SDL_GetKeyName(static_cast<SDLKey>(i));
    string2key[key_name] = static_cast<SDLKey>(i);

    // FIXME: Make the keynames somewhere user visible so that users can use them
    log_debug("Key: '{}'", key_name);
  }
}

SDLDriver::~SDLDriver()
{

}

Keyboard*
SDLDriver::create_keyboard(const FileReader& /*reader*/, Control* parent)
{
  return (keyboard_binding = new Keyboard(parent));
}

Button*
SDLDriver::create_button(const FileReader& reader, Control* parent)
{
  //log_info("SDL: {}", reader.get_name());
  if (reader.get_name() == "sdl:joystick-button")
  {
    JoystickButtonBinding binding;

    reader.read_int("device", binding.device);
    reader.read_int("button", binding.button);

    if (open_joystick(binding.device))
    {
      binding.binding = new Button(parent);
      joystick_button_bindings.push_back(binding);

      return binding.binding;
    }
    else
    {
      return 0;
    }
  }
  else if (reader.get_name() == "sdl:joystick-hat")
  {
    JoystickHatBinding binding;

    reader.read_int("device", binding.device);
    reader.read_int("hat",    binding.hat);

    std::string dir;
    if (reader.read_string("dir", dir))
    {
      if (dir == "up")         binding.dir = SDL_HAT_UP;
      else if (dir == "down")  binding.dir = SDL_HAT_DOWN;
      else if (dir == "left")  binding.dir = SDL_HAT_LEFT;
      else if (dir == "right") binding.dir = SDL_HAT_RIGHT;
      else {
        log_error("unknown hat direction '{}'", dir);
        return 0;
      }

      if (open_joystick(binding.device))
      {
        binding.binding = new Button(parent);
        joystick_hat_bindings.push_back(binding);
        return binding.binding;
      }
    }
    else
    {
      log_error("'dir' missing for joystick-hat binding");
      return 0;
    }
    return 0;
  }
  else if (reader.get_name() == "sdl:mouse-button")
  {
    MouseButtonBinding binding;

    reader.read_int("button", binding.button);
    binding.binding = new Button(parent);
    mouse_button_bindings.push_back(binding);

    return binding.binding;
  }
  else if (reader.get_name() == "sdl:keyboard-button")
  {
    std::string key;
    if (reader.read_string("key", key))
    {
      String2Key::iterator i = string2key.find(key);
      if (i != string2key.end())
      {
        KeyboardButtonBinding binding;

        binding.key = i->second;
        binding.binding = new Button(parent);
        keyboard_button_bindings.push_back(binding);

        return binding.binding;
      }
      else
      {
        log_error("couldn't find keysym for key '{}'", key);
        return 0;
      }
    }
    else
    {
      log_error("'key' missing");
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

Axis*
SDLDriver::create_axis(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "sdl:joystick-axis")
  {
    JoystickAxisBinding binding;

    reader.read_int("device", binding.device);
    reader.read_int("axis",   binding.axis);

    if (open_joystick(binding.device))
    {
      binding.binding = new Axis(parent);
      joystick_axis_bindings.push_back(binding);

      return binding.binding;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

Scroller*
SDLDriver::create_scroller(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "sdl:mouse-scroller")
  {
    ScrollerBinding binding;

    binding.binding = new Scroller(parent);
    scroller_bindings.push_back(binding);

    return binding.binding;
  }
  else
  {
    return 0;
  }
}

Pointer*
SDLDriver::create_pointer(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "sdl:mouse-pointer")
  {
    PointerBinding binding;

    binding.binding = new Pointer(parent);
    pointer_bindings.push_back(binding);

    return binding.binding;
  }
  else
  {
    return 0;
  }
}

bool
SDLDriver::open_joystick(int device)
{
  JoystickHandles::iterator i = joystick_handles.find(device);
  if (i == joystick_handles.end())
  {
    SDL_Joystick* joy = SDL_JoystickOpen(device);
    if (joy)
    {
      joystick_handles[device] = joy;
      return true;
    }
    else
    {
      log_error("couldn't open joystick number {}", device);
      return false;
    }
  }
  else
  {
    return true;
  }
}

void
SDLDriver::update(float delta)
{
  // FIXME: Little hackywacky, better way would be to fetch event
  // loops somewhere else and only forward the relevant SDL_Events to
  // the SDLDriver

  // --- Joystick Mouse Emulation ---
  const float deadzone = 0.15f;
  const float speed = 800.0f; // Pixels per second

  bool joy_moved = false;

  if (std::abs(joy_axis_x) > deadzone) {
    virtual_mouse_x += joy_axis_x * speed * delta;
    joy_moved = true;
  }
  if (std::abs(joy_axis_y) > deadzone) {
    virtual_mouse_y += joy_axis_y * speed * delta;
    joy_moved = true;
  }

  if (joy_moved) {
    Size screen_size = Display::get_size();
    if (virtual_mouse_x < 0) virtual_mouse_x = 0;
    if (virtual_mouse_y < 0) virtual_mouse_y = 0;
    if (virtual_mouse_x > screen_size.width) virtual_mouse_x = screen_size.width;
    if (virtual_mouse_y > screen_size.height) virtual_mouse_y = screen_size.height;

    for(std::vector<PointerBinding>::iterator i = pointer_bindings.begin();
        i != pointer_bindings.end(); ++i)
    {
      Vector2f new_pos(virtual_mouse_x, virtual_mouse_y);

      // Force update by jittering inward to ensure valid bounds.
      if (i->binding->get_pos() == new_pos)
      {
          Vector2f temp_pos = new_pos;
          temp_pos.x += (new_pos.x > screen_size.width / 2.0f) ? -1.0f : 1.0f;
          temp_pos.y += (new_pos.y > screen_size.height / 2.0f) ? -1.0f : 1.0f;
          i->binding->set_pos(temp_pos);
      }

      i->binding->set_pos(new_pos);
    }
  }
  // --------------------------------

  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT: // FIXME: make this into a GameEvent
        ScreenManager::instance()->pop_all_screens();
        break;

      case SDL_MOUSEMOTION:
        // Sync virtual mouse with IR pointer
        virtual_mouse_x = (float)event.motion.x;
        virtual_mouse_y = (float)event.motion.y;

        for(std::vector<PointerBinding>::iterator i = pointer_bindings.begin();
            i != pointer_bindings.end(); ++i)
        {
          i->binding->set_pos(Vector2f(event.motion.x, event.motion.y));
        }

        for(std::vector<ScrollerBinding>::iterator i = scroller_bindings.begin();
            i != scroller_bindings.end(); ++i)
        {
          i->binding->set_delta(Vector2f(event.motion.xrel, event.motion.yrel));
        }
        break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        for(std::vector<MouseButtonBinding>::iterator i = mouse_button_bindings.begin();
            i != mouse_button_bindings.end(); ++i)
        {
          if (event.button.button == (*i).button)
          {
            if (event.button.state == SDL_PRESSED)
              (*i).binding->set_state(BUTTON_PRESSED);
            else
              (*i).binding->set_state(BUTTON_RELEASED);
          }
        }
        break;

      case SDL_VIDEORESIZE:
        Display::resize(Size(event.resize.w, event.resize.h));
        break;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        // keyboard events
        if (keyboard_binding)
          keyboard_binding->send_char(event.key);

        // global event hacks
        if (event.key.state == SDL_PRESSED)
          global_event.on_button_press(event.key);
        else
          global_event.on_button_release(event.key);

        // game button events
        for(std::vector<KeyboardButtonBinding>::iterator i = keyboard_button_bindings.begin();
            i != keyboard_button_bindings.end(); ++i)
        {
          if (event.key.keysym.sym == i->key)
          {
            if (event.key.state == SDL_PRESSED)
              i->binding->set_state(BUTTON_PRESSED);
            else
              i->binding->set_state(BUTTON_RELEASED);
          }
        }
        break;

      case SDL_JOYHATMOTION:
        for(std::vector<JoystickHatBinding>::iterator i = joystick_hat_bindings.begin();
            i != joystick_hat_bindings.end(); ++i)
        {
          if (event.jhat.which == i->device &&
              event.jhat.hat   == i->hat)
          {
            bool active = (event.jhat.value & i->dir);
            i->binding->set_state(active ? BUTTON_PRESSED : BUTTON_RELEASED);
          }
        }
        break;

      case SDL_JOYAXISMOTION:
        // Capture Axis 0/1 from ANY device for mouse emulation
        if (event.jaxis.axis == 0) {
            joy_axis_x = static_cast<float>(event.jaxis.value) / 32767.0f;
        } else if (event.jaxis.axis == 1) {
            joy_axis_y = static_cast<float>(event.jaxis.value) / 32767.0f;
        }

        for(std::vector<JoystickAxisBinding>::iterator i = joystick_axis_bindings.begin();
            i != joystick_axis_bindings.end(); ++i)
        {
          if (event.jaxis.which == i->device &&
              event.jaxis.axis  == i->axis)
            i->binding->set_state(static_cast<float>(event.jaxis.value) / 32767.0f);
        }
        break;

      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        for(std::vector<JoystickButtonBinding>::iterator i = joystick_button_bindings.begin();
            i != joystick_button_bindings.end(); ++i)
        {
          if (event.jbutton.which  == i->device &&
              event.jbutton.button == i->button)
          {
            i->binding->set_state(event.jbutton.state == SDL_PRESSED ? BUTTON_PRESSED : BUTTON_RELEASED);
          }
        }
        break;

      default:
        // FIXME: Do something with other events
        break;
    }
  }
}

} // namespace Input

// EOF
