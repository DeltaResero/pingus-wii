// src/engine/input/driver_factory.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_INPUT_DRIVER_FACTORY_HPP
#define HEADER_PINGUS_ENGINE_INPUT_DRIVER_FACTORY_HPP

#include <memory>
#include <string>

namespace pingus::input {

class Driver;
class Manager;

class DriverFactory
{
private:
public:
  static std::unique_ptr<Driver> create(const std::string& name, Manager* manager);

private:
  DriverFactory(const DriverFactory&);
  DriverFactory& operator=(const DriverFactory&);
};

} // namespace pingus::input

#endif

// EOF
