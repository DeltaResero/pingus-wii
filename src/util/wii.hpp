// src/util/wii.hpp
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

#ifndef HEADER_PINGUS_UTIL_WII_HPP
#define HEADER_PINGUS_UTIL_WII_HPP

#ifdef __WII__

#include <string>

namespace Wii {

/** Mount the SD card
 *  @return true if successful, false otherwise */
bool mount_sd();

/** Unmount the SD card */
void unmount_sd();

/** Mount a USB storage device
 *  @return true if successful, false otherwise */
bool mount_usb();

/** Unmount the USB storage device */
void unmount_usb();

/** Get the base directory for Pingus on the Wii
 *  This will search for the data directory on USB first, then SD
 *  @return The base directory path (e.g., "sd:/apps/pingus/")
 *  @throws std::runtime_error if no valid installation is found */
std::string get_base_dir();

/** Get the data directory for Pingus on the Wii
 *  @return The data directory path (e.g., "sd:/apps/pingus/data/")
 *  @throws std::runtime_error if no valid installation is found */
std::string get_data_dir();

} // namespace Wii

#endif // __WII__

#endif // HEADER_PINGUS_UTIL_WII_HPP

// EOF
