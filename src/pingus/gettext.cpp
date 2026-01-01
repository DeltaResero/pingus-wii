// src/pingus/gettext.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "tinygettext/dictionary_manager.hpp"

tinygettext::DictionaryManager dictionary_manager;

std::string _(const std::string& msg) {
  return dictionary_manager.get_dictionary().translate(msg);
}

std::string _(const std::string& msg, const std::string& msg_pl, int num) {
  return dictionary_manager.get_dictionary().translate_plural(msg, msg_pl, num);
}

// EOF
