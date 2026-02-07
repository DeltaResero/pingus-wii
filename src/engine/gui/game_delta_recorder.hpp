// src/engine/gui/game_delta_recorder.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_GUI_GAME_DELTA_RECORDER_HPP
#define HEADER_PINGUS_ENGINE_GUI_GAME_DELTA_RECORDER_HPP

namespace pingus {

class GameDeltaRecorder
{
private:

  public:
  GameDeltaRecorder ();
  GameDelta* get ();
};


} // namespace pingus
#endif

// EOF
