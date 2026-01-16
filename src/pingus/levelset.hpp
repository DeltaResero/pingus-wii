// src/pingus/levelset.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_LEVELSET_HPP
#define HEADER_PINGUS_PINGUS_LEVELSET_HPP

#include "engine/display/sprite.hpp"
#include "pingus/pingus_level.hpp"
#include "util/pathname.hpp"

class Levelset
{
public:
  struct Level
  {
    std::string resname;
    bool accessible;
    bool finished;
    PingusLevel plf;

    Level() :
      resname(),
      accessible(),
      finished(),
      plf()
    {}
  };

private:
  std::string m_title;
  std::string m_description;
  bool m_developer_only;
  float m_priority;
  Sprite m_sprite;
  int  m_completion;
  std::vector<std::unique_ptr<Level>> m_levels;

public:
  static std::unique_ptr<Levelset> from_file(const Pathname& pathname);
  static std::unique_ptr<Levelset> from_directory(const std::string& title,
                                                  const std::string& description,
                                                  const std::string& image,
                                                  const Pathname& pathname);

public:
  Levelset();
  ~Levelset();

  void set_title(const std::string& title);
  void set_description(const std::string& description);
  void set_image(const std::string& image);
  void set_developer_only(bool developer_only);
  void set_priority(float priority);
  void add_level(const std::string& resname, bool accessible = false);

  bool get_developer_only() const;
  float  get_priority() const;
  std::string get_title() const;
  std::string get_description() const;
  Sprite get_image() const;

  Level* get_level(int num) const;
  int get_level_count() const;

  /** Return the number of completed levels */
  int get_completion()  const;

  void refresh();
private:
  Levelset (const Levelset&);
  Levelset& operator= (const Levelset&);
};

#endif

// EOF
