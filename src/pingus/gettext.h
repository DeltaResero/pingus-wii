// src/pingus/gettext.h
// SPDX-License-Identifier: GPL-3.0-or-later
//
// TinyGetText - A small flexible gettext() replacement
// Copyright (C) 2004 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_GETTEXT_HXX
#define HEADER_GETTEXT_HXX

#include <string>

std::string _(const std::string& msg);
std::string _(const std::string& msg, const std::string& msg_pl, int num);

#endif /* HEADER_GETTEXT_HXX */

// EOF
