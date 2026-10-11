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
#include <unistd.h>

#include <fat.h>
#include <ogc/system.h>
#include <ogc/usbstorage.h>
#include <sdcard/wiisd_io.h>
#include <wiiuse/wpad.h>

// SDL's event pump sends SDL_QUIT while this is set.
extern "C" bool OGC_ResetRequested;

namespace pingus {


namespace {

// Pages of cache, and sectors per page, handed to libfat for each device.
const int CACHE_PAGES = 32;
const int SECTORS_PER_PAGE = 64;

// Checks for a USB drive, 50 ms apart, before giving up on it.
const int USB_TRIES = 20;
const useconds_t USB_TRY_DELAY = 50000;

const char* const APP_SUBDIR = "apps/pingus";

// Global state for mounted devices
bool g_sd_mounted = false;
bool g_usb_mounted = false;
std::string g_base_dir;

// Set from an interrupt.
volatile bool g_power_off_requested = false;

// A released device has to drop the cached path naming it.
void forget_base_dir(const std::string& device)
{
  if (g_base_dir.compare(0, device.size(), device) == 0)
    g_base_dir.clear();
}

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

void on_power_button()
{
  g_power_off_requested = true;
  OGC_ResetRequested = true;
}

void on_remote_power_button(s32)
{
  on_power_button();
}

} // anonymous namespace

namespace Wii {

bool mount_sd()
{
  if (g_sd_mounted)
    return true;

  if (!__io_wiisd.startup())
    return false;

  // A slot with no card in it starts up and then reports nothing inserted.
  if (!__io_wiisd.isInserted())
  {
    __io_wiisd.shutdown();
    return false;
  }

  // SDL2main has already mounted it with libfat's small cache.
  fatUnmount("sd:");
  g_sd_mounted = fatMount("sd", &__io_wiisd, 0, CACHE_PAGES, SECTORS_PER_PAGE);
  if (!g_sd_mounted)
    __io_wiisd.shutdown();

  return g_sd_mounted;
}

void unmount_sd()
{
  if (!g_sd_mounted)
    return;

  // Without the colon, libfat unmounts the current directory's device.
  fatUnmount("sd:");
  __io_wiisd.shutdown();
  g_sd_mounted = false;
  forget_base_dir("sd:/");
}

bool mount_usb()
{
  if (g_usb_mounted)
    return true;

  __io_usbstorage.startup();

  // A drive behind a hub can take a moment to answer.
  for (int i = 1; i < USB_TRIES && !__io_usbstorage.isInserted(); ++i)
    usleep(USB_TRY_DELAY);

  fatUnmount("usb:");
  g_usb_mounted = fatMount("usb", &__io_usbstorage, 0, CACHE_PAGES, SECTORS_PER_PAGE);
  if (!g_usb_mounted)
    __io_usbstorage.shutdown();

  return g_usb_mounted;
}

void unmount_usb()
{
  if (!g_usb_mounted)
    return;

  fatUnmount("usb:");
  __io_usbstorage.shutdown();
  g_usb_mounted = false;
  forget_base_dir("usb:/");
}

std::string get_base_dir()
{
  if (!g_base_dir.empty())
    return g_base_dir;

  // USB first: it is the faster of the two where both are present.
  if (mount_usb())
  {
    const std::string path = std::string("usb:/") + APP_SUBDIR + "/";
    if (dir_exists(path))
    {
      g_base_dir = path;
      return g_base_dir;
    }
    unmount_usb();
  }

  if (mount_sd())
  {
    const std::string path = std::string("sd:/") + APP_SUBDIR + "/";
    if (dir_exists(path))
    {
      g_base_dir = path;
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

void take_power_buttons()
{
  SYS_SetPowerCallback(on_power_button);
  WPAD_SetPowerButtonCallback(on_remote_power_button);
}

void power_off_if_requested()
{
  if (!g_power_off_requested)
    return;

  SYS_ResetSystem(SYS_POWEROFF, 0, 0);

  // libogc returns if IOS hasn't cut the power yet, with IOS already gone.
  while (g_power_off_requested)
  {
  }
}

} // namespace Wii


} // namespace pingus
#endif // __WII__

// EOF
