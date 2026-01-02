// test/utf8_test.cpp
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

#include "util/utf8.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " TEXT" << std::endl;
  }
  else
  {
    std::cout << "length in ASCII characters: " << std::string(argv[1]).length() << std::endl;
    std::cout << "length in UTF8 characters:  " << UTF8::length(argv[1]) << std::endl;

    std::string res = UTF8::substr(argv[1], 1, 1);
    std::cout << "substr:  " << res.length() << " " << res << std::endl;
  }
  return 0;
}

// EOF
