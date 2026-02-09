// src/engine/sound/sound_res_mgr.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/sound/sound_res_mgr.hpp"

#include "pingus/globals.hpp"
#include "pingus/path_manager.hpp"
#include "util/log.hpp"

namespace pingus {


SoundResMgr::SoundMap SoundResMgr::sound_map;

SoundHandle
SoundResMgr::load(std::string_view name)
{
  // Transparent lookup using string_view
  auto i = sound_map.find(name);

  if (i == sound_map.end())
  {
    // Optimize string construction by pre-allocating memory
    std::string filename;
    filename.reserve(8 + name.size() + 4); // "sounds/" (7) + "/" (1) + name + ".wav" (4)
    filename = "sounds/";
    filename += name;
    filename += ".wav";

    std::string full_path = g_path_manager.complete(filename);
    Mix_Chunk* chunk = Mix_LoadWAV(full_path.c_str());

    if (!chunk)
    {
      log_error("SoundResMgr: Failed to load sound '{}' from '{}': {}", name, full_path, Mix_GetError());
      // Negative cache: prevent repeated load attempts
      sound_map.emplace(std::string(name), nullptr);
      return nullptr;
    }

    log_info("SoundResMgr: Loaded sound '{}' from disk: {}", name, full_path);

    // Store in map with ownership
    auto& stored_ptr = sound_map.emplace(std::string(name), SoundPtr(chunk)).first->second;
    return stored_ptr.get();
  }
  else
  {
    // Cache hit - return immediately without logging (console I/O is slow on Wii)
    return i->second.get();
  }
}

void SoundResMgr::free_sound_map()
{
  // unique_ptr handles deletion automatically
  sound_map.clear();
}


} // namespace pingus

// EOF
