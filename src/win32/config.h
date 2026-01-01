// src/win32/config.h
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef PINGUS_CONFIG_H
#define PINGUS_CONFIG_H

#include <assert.h>

#define PACKAGE "Pingus"
#define VERSION  "0.7.2"
#define PACKAGE_STRING "Pingus 0.7.2"
#define MAJOR_VERSION 0
#define MINOR_VERSION 7
#define PATCH_VERSION 2
#define VERSION_STRING "0.7.2"
#define PINGUS_DATADIR "data"
#define ENABLE_NLS 1

/* 'real' config values */
#define HAVE_STDDEF_H 1
#define HAVE_STRING_H 1
#define HAVE_STDLIB_H 1
#define HAVE_ALLOCA 1
#define HAVE_GETCWD 1
#define HAVE_SETLOCALE 1
#define HAVE_STRDUP 1
#define HAVE_GETTEXT 1
#define ICONV_CONST const

/* MSVC specifics */
#if defined(_MSC_VER) && !defined(__cplusplus)
#define inline __inline
#endif

#define alloca _alloca
#define getcwd _getcwd
// ????
#define LOCALEDIR "."
#define LOCALE_ALIAS_PATH "."

typedef unsigned __int64 uintmax_t;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define PATH_MAX _MAX_PATH

#endif

// EOF
