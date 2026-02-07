// src/pingus/groundtype.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/groundtype.hpp"

#include "util/log.hpp"

namespace pingus {


Groundtype::GPType
Groundtype::string_to_type(const std::string& arg_type)
{
  if (arg_type == "solid")
    return Groundtype::GP_SOLID;
  else if (arg_type == "transparent")
    return Groundtype::GP_TRANSPARENT;
  else if (arg_type == "ground")
    return Groundtype::GP_GROUND;
  else if (arg_type == "bridge")
    return Groundtype::GP_BRIDGE;
  else if (arg_type == "water")
    return Groundtype::GP_WATER;
  else if (arg_type == "lava")
    return Groundtype::GP_LAVA;
  else if (arg_type == "remove")
    return Groundtype::GP_REMOVE;
  else
  {
    log_error("Groundtype: Unhandled type: '{}'", arg_type);
    return Groundtype::GP_GROUND;
  }
}

std::string
Groundtype::type_to_string(GPType arg_type)
{
  switch (arg_type)
  {
    case Groundtype::GP_SOLID:
      return "solid";
    case Groundtype::GP_TRANSPARENT:
      return "transparent";
    case Groundtype::GP_GROUND:
      return "ground";
    case Groundtype::GP_BRIDGE:
      return "bridge";
    case Groundtype::GP_WATER:
      return "water";
    case Groundtype::GP_LAVA:
      return "lava";
    case Groundtype::GP_REMOVE:
      return "remove";
    default:
      log_error("Groundtype: Unhandled type: {}", static_cast<int>(arg_type));
      return "ground";
  }
}


} // namespace pingus

// EOF
