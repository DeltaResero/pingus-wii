// test/system_normalize_path_test.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include <assert.h>

#include "util/system.hpp"

using namespace pingus;

int main(int argc, char** argv)
{
  assert(System::normalize_path("") == "");
  assert(System::normalize_path("/") == "/");
  assert(System::normalize_path("abc") == "abc");

  assert(System::normalize_path("/abc") == "/abc");
  assert(System::normalize_path("/../..") == "/");
  assert(System::normalize_path("a/../..") == "..");
  assert(System::normalize_path("a////c") == "a/c");
  assert(System::normalize_path("a//..///c") == "c");
  assert(System::normalize_path("/a//..///c") == "/c");
  assert(System::normalize_path("/a/../../b/c") == "/b/c");
  assert(System::normalize_path("../foo/bar/") == "../foo/bar");

  return 0;
}

// EOF
