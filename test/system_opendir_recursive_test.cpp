// test/system_opendir_recursive_test.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2024 [Your Name/Alias]
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include <iostream>

#include "util/system.hpp"

int main(int argc, char** argv)
{
  for(int i = 1; i < argc; ++i)
  {
    std::vector<std::string> lst = System::opendir_recursive(argv[i]);
    for(auto it = lst.begin(); it != lst.end(); ++it)
    {
      std::cout << *it << std::endl;
    }
  }
  return 0;
}

// EOF
