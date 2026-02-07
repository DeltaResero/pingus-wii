// src/util/log.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2026 DeltaResero
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_UTIL_LOG_HPP
#define HEADER_PINGUS_UTIL_LOG_HPP

#ifdef LOGGING_ENABLED

#include <atomic>
#include <format>
#include <iostream>
#include <string>
#include <string_view>

// Keep the logmich namespace for set_log_level to minimize changes in existing code.
namespace logmich {
enum LogLevel {
  kNone,
  kError,
  kWarning,
  kInfo,
  kDebug,
  kTmp // We'll treat Tmp as Debug
};

// Use an atomic for thread-safe access to the log level.
inline std::atomic<LogLevel> current_log_level = kWarning;

inline void set_log_level(LogLevel level) { current_log_level.store(level); }
} // namespace logmich

// Templated function to handle type-safe formatting with std::format.
template <typename... Args>
void log_message(logmich::LogLevel level, std::string_view prefix,
                 std::string_view fmt, Args &&...args) {
  if (level <= logmich::current_log_level.load(std::memory_order_relaxed)) {
    std::ostream &out = (level == logmich::kError || level == logmich::kWarning)
                            ? std::cerr
                            : std::cout;
    try {
      out << prefix << std::vformat(fmt, std::make_format_args(args...))
          << std::endl;
    } catch (const std::format_error &e) {
      out << prefix << "!!! FORMAT ERROR: " << e.what()
          << " | Original format string: " << fmt << " !!!" << std::endl;
    }
  }
}

// Variadic macros that forward to the templated function.
#define log_error(fmt, ...)                                                    \
  log_message(logmich::kError, "[ERROR] ", fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)                                                     \
  log_message(logmich::kWarning, "[WARN]  ", fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)                                                     \
  log_message(logmich::kInfo, "[INFO]  ", fmt, ##__VA_ARGS__)
#define log_debug(fmt, ...)                                                    \
  log_message(logmich::kDebug, "[DEBUG] ", fmt, ##__VA_ARGS__)
#define log_tmp(fmt, ...)                                                      \
  log_message(logmich::kTmp, "[TMP]   ", fmt, ##__VA_ARGS__)

#else // LOGGING_ENABLED is not defined

// Dummy implementation that compiles to nothing for release/Wii builds.
namespace logmich {
enum LogLevel { kNone, kError, kWarning, kInfo, kDebug, kTmp };
inline void set_log_level(LogLevel) {}
} // namespace logmich

#define log_error(...)                                                         \
  do {                                                                         \
  } while (0)
#define log_warn(...)                                                          \
  do {                                                                         \
  } while (0)
#define log_info(...)                                                          \
  do {                                                                         \
  } while (0)
#define log_debug(...)                                                         \
  do {                                                                         \
  } while (0)
#define log_tmp(...)                                                           \
  do {                                                                         \
  } while (0)

#endif // LOGGING_ENABLED

#endif // HEADER_PINGUS_UTIL_LOG_HPP
