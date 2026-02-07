// src/util/wii.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2012 r-win <r-win@live.com>
// Copyright (C) 2026 DeltaResero
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifdef __WII__

#include "util/wii.hpp"

#include <dirent.h>
#include <stdexcept>

#include <fat.h>
#include <ogc/usbstorage.h>
#include <sdcard/wiisd_io.h>

#define CACHE_SIZE 32
#define SECTOR_SIZE 64

namespace pingus {


namespace {

// Global state for mounted devices
bool g_sd_mounted = false;
bool g_usb_mounted = false;
std::string g_base_dir;

bool dir_exists(const std::string& directory)
{
  DIR* dp = opendir(directory.c_str());
  if (dp != nullptr)
  {
    closedir(dp);
    return true;
  }
  return false;
}

} // anonymous namespace

namespace Wii {

bool mount_sd()
{
  if (g_sd_mounted)
    return true;

  if (!__io_wiisd.startup())
    return false;

  if (!__io_wiisd.isInserted())
  {
    __io_wiisd.shutdown();
    return false;
  }

  g_sd_mounted = fatMount("sd", &__io_wiisd, 0, CACHE_SIZE, SECTOR_SIZE);
  return g_sd_mounted;
}

void unmount_sd()
{
  if (g_sd_mounted)
  {
    fatUnmount("sd");
    __io_wiisd.shutdown();
    g_sd_mounted = false;
  }
}

bool mount_usb()
{
  if (g_usb_mounted)
    return true;

  __io_usbstorage.startup();
  g_usb_mounted = fatMount("usb", &__io_usbstorage, 0, CACHE_SIZE, SECTOR_SIZE);
  return g_usb_mounted;
}

void unmount_usb()
{
  if (g_usb_mounted)
  {
    fatUnmount("usb");
    __io_usbstorage.shutdown();
    g_usb_mounted = false;
  }
}

std::string get_base_dir()
{
  // Return cached value if already found
  if (!g_base_dir.empty() && (g_usb_mounted || g_sd_mounted))
    return g_base_dir;

  // Try USB first (typically faster)
  if (mount_usb())
  {
    std::string usb_path = "usb:/apps/pingus";
    if (dir_exists(usb_path))
    {
      g_base_dir = usb_path + "/";
      return g_base_dir;
    }
    unmount_usb();
  }

  // Fall back to SD card
  if (mount_sd())
  {
    std::string sd_path = "sd:/apps/pingus";
    if (dir_exists(sd_path))
    {
      g_base_dir = sd_path + "/";
      return g_base_dir;
    }
    unmount_sd();
  }

  throw std::runtime_error(
    "Pingus installation not found!\n"
    "Expected location: usb:/apps/pingus/ or sd:/apps/pingus/\n"
    "Please ensure Pingus is properly installed to your SD card or USB device."
  );
}

std::string get_data_dir()
{
  std::string base = get_base_dir();
  std::string data_path = base + "data/";

  if (!dir_exists(data_path))
  {
    throw std::runtime_error(
      "Pingus data directory not found at: " + data_path + "\n"
      "Please ensure the data/ folder is present in your Pingus installation."
    );
  }

  return data_path;
}

} // namespace Wii


} // namespace pingus
#endif // __WII__

// EOF
