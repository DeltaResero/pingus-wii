// test/system_write_file_util.cpp
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

#include "util/pathname.hpp"
#include "util/system.hpp"

using namespace pingus;

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " OUTFILE CONTENT" << std::endl;
    return 1;
  }
  else
  {
    System::write_file(argv[1], argv[2]);
  }

  return 0;
}

// EOF
