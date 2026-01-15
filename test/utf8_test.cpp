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
#include <string>

#include "util/utf8.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " TEXT" << std::endl;
  }
  else
  {
    std::string text(argv[1]);

    std::cout << "length in ASCII characters: " << text.length() << std::endl;
    std::cout << "length in UTF8 characters:  " << UTF8::length(text) << std::endl;

    std::string res = UTF8::substr(text, 1, 1);
    std::cout << "substr:  " << res.length() << " " << res << std::endl;
  }
  return 0;
}

// EOF
