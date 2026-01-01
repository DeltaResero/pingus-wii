// src/pingus/prefab_file.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_PREFAB_FILE_HPP
#define HEADER_PINGUS_PINGUS_PREFAB_FILE_HPP

#include <vector>

#include "util/file_reader.hpp"
#include "util/pathname.hpp"

class PrefabFile
{
public:
  static PrefabFile from_resource(const std::string& name);
  static PrefabFile from_path(const Pathname& file);

private:
  std::string m_name;
  std::vector<FileReader> m_objects;
  FileReader m_overrides;

private:
  PrefabFile(const std::string& filename, const std::vector<FileReader>& objects,
             const FileReader& overrides);

public:
  const std::vector<FileReader>& get_objects() const;
  FileReader get_overrides() const;
};

#endif

// EOF
