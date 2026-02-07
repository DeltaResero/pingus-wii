// src/util/overrride_file_reader.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_UTIL_OVERRIDE_FILE_READER_HPP
#define HEADER_PINGUS_UTIL_OVERRIDE_FILE_READER_HPP

#include "util/file_reader.hpp"

namespace pingus {


/** */
class OverrideFileReader : public FileReader
{
public:
  OverrideFileReader(const FileReader& reader,
                     const FileReader& overrides);
};


} // namespace pingus
#endif

// EOF
