// src/pingus/action_name.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTION_NAME_HPP
#define HEADER_PINGUS_PINGUS_ACTION_NAME_HPP

#include <string>

namespace pingus {

namespace ActionName {

/** The order of the actions here are the same as the order of actions
    in the buttonpanel, so if the order in the buttonpanel is not what
    it should be it needs to be changed here. */
enum Enum
{
  ANGEL,
  BASHER,
  BLOCKER,
  BOARDER,
  BOMBER,
  BRIDGER,
  CLIMBER,
  DIGGER,
  DROWN,
  EXITER,
  FALLER,
  FLOATER,
  JUMPER,
  LASERKILL,
  MINER,
  SLIDER,
  SMASHED,
  SPLASHED,
  SUPERMAN,
  TELEPORTED,
  WAITER,
  WALKER
};

/** Converts a action enum into its internal string representation, as
    used in the xml or the resource files Bomber => "bomber" */
std::string to_string(Enum action);

/** Converts a internal action string back into its action enum
    representation  "bomber" => Bomber */
Enum from_string(const std::string& action);

/** Convert a action enum into its visual representation, aka the
    thing that is seen on the screen for the user Bomber => "Bomber" */
std::string to_screenname(Enum action);

} // namespace ActionName


} // namespace pingus
#endif

// EOF
