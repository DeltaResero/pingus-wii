// src/engine/sound/sound_impl.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_SOUND_SOUND_IMPL_HPP
#define HEADER_PINGUS_ENGINE_SOUND_SOUND_IMPL_HPP

#include <string_view>

namespace pingus::sound {

class PingusSoundImpl
{
public:
  PingusSoundImpl () { };
  virtual ~PingusSoundImpl () { };

  /** Load a music file and play it immediately.
      @param filename The complete filename
      @param volume   The volume to play the music with  */
  virtual void real_play_music(std::string_view filename, float volume, bool loop) = 0;

  /** Stops playing any music file */
  virtual void real_stop_music() = 0;

  /** Load a sound file and play it immediately
      @param filename The complete filename
      @param volume   The volume to play the sound at
      @param panning  The panning to play the sound with */
  virtual void real_play_sound(std::string_view filename,
                               float volume, float panning) = 0;

  virtual void set_sound_volume(float volume) = 0;
  virtual void set_music_volume(float volume) = 0;
  virtual void set_master_volume(float volume) = 0;

  virtual float get_sound_volume() const = 0;
  virtual float get_music_volume() const = 0;
  virtual float get_master_volume() const = 0;

}; // class PingusSoundImpl

}  // namespace pingus::sound

#endif

// EOF
