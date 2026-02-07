// src/pingus/pingus_demo.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/pingus_demo.hpp"

#include <stdexcept>

#include "util/file_reader.hpp"
#include "util/pathname.hpp"
#include "util/log.hpp"
#include "util/raise_exception.hpp"

namespace pingus {


PingusDemo::PingusDemo(const Pathname& pathname) :
  m_levelname(),
  m_checksum(),
  m_events()
{
  std::vector<FileReader> lines = FileReader::parse_many(pathname);

  if (lines.empty())
  {
    raise_exception(std::runtime_error, "'" << pathname.str() << "', demo file is empty");
  }
  else
  {
    if (lines.front().get_name() == "level")
    {
      const FileReader& reader = lines.front();
      if (!reader.read_string("name", m_levelname))
      {
        raise_exception(std::runtime_error, "(level (name ...)) entry missing in demo file '" << pathname.str() << "'");
      }

      reader.read_string("checksum", m_checksum);
    }

    for(std::vector<FileReader>::iterator i = lines.begin()+1; i != lines.end(); ++i)
    {
      if (i->get_name() != "checksum") // workaround for old incorrectly recorded demo files
      {
        m_events.push_back(ServerEvent(*i));
      }
    }
  }
}


} // namespace pingus

// EOF
