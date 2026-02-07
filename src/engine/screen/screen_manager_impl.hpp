// src/engine/screen/screen_manager_impl.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_SCREEN_SCREEN_MANAGER_IMPL_HPP
#define HEADER_PINGUS_ENGINE_SCREEN_SCREEN_MANAGER_IMPL_HPP

#include "engine/screen/pingus.hpp"

namespace pingus {

class ScreenManagerImpl
{
private:
  typedef enum { PINGUSMAIN_MENU } States;
public:
  ScreenManagerImpl ();
  ~ScreenManagerImpl ();

  void display ();

private:
  ScreenManagerImpl (const ScreenManagerImpl&);
  ScreenManagerImpl& operator= (const ScreenManagerImpl&);
};


} // namespace pingus
#endif

// EOF
