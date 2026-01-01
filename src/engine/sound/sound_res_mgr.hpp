// src/engine/sound/sound_res_mgr.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_SOUND_SOUND_RES_MGR_HPP
#define HEADER_PINGUS_ENGINE_SOUND_SOUND_RES_MGR_HPP

#include <map>
#include <string>
#include <SDL_mixer.h>

typedef Mix_Chunk* SoundHandle;

class SoundResMgr
{
private:
  typedef std::map<std::string, Mix_Chunk*> SoundMap;
  static SoundMap sound_map;

public:
  static SoundHandle load(const std::string& name);
  static void free_sound_map();
private:
  SoundResMgr (const SoundResMgr&);
  SoundResMgr& operator= (const SoundResMgr&);
};

#endif

// EOF
