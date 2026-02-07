// test/system_normalize_path_util.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include <iostream>

#include "util/system.hpp"

using namespace pingus;

int main(int argc, char** argv)
{
  for(int i = 1; i < argc; ++i)
  {
    std::cout << System::normalize_path(argv[i]) << std::endl;
  }

  return 0;
}

// EOF
