# CMakeLists.txt
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Pingus
# Copyright (C) 2026 DeltaResero
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

cmake_minimum_required(VERSION 3.10)

# Prevent in-source builds
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed. Please create a build directory and run cmake from there:\n"
                      "  mkdir build\n"
                      "  cd build\n"
                      "  cmake ..\n")
endif()

project(Pingus VERSION 0.7.7 LANGUAGES C CXX)

# We define the full version string manually for the game to display
set(PROJECT_FULL_VERSION "v0.7.7-wii-d.01")
set(VERSION ${PROJECT_FULL_VERSION})

# Build Type Configuration (Default to Release)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# Verify strip tool is found by the toolchain
if(CMAKE_STRIP)
  message(STATUS "Found strip tool: ${CMAKE_STRIP}")
else()
  message(WARNING "Strip tool not found. Release binaries will not be stripped.")
endif()

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect Wii build
if(CMAKE_SYSTEM_NAME STREQUAL "NintendoWii")
  set(WII_BUILD ON)
  message(STATUS "Configuring for Nintendo Wii")
  add_compile_definitions(__WII__ GEKKO)
else()
  set(WII_BUILD OFF)
endif()

# Cross-compilation safety check
if(CMAKE_CROSSCOMPILING AND NOT WII_BUILD)
  message(WARNING "Cross-compiling detected but not for Wii. "
                  "If this is unintentional, please check your toolchain file.")
endif()

# Wii-specific environment validation
if(WII_BUILD)
  # Verify DEVKITPRO environment
  if(NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "DEVKITPRO environment variable not set. "
                        "Please set it to your devkitPro installation path.")
  endif()
  
  # Verify required tools exist
  if(NOT EXISTS "$ENV{DEVKITPRO}/tools/bin/elf2dol")
    message(FATAL_ERROR "elf2dol not found at $ENV{DEVKITPRO}/tools/bin/elf2dol. "
                        "Please check your devkitPro installation.")
  endif()
  
  # Verify required libraries exist
  if(NOT EXISTS "$ENV{DEVKITPRO}/libogc")
    message(FATAL_ERROR "libogc not found at $ENV{DEVKITPRO}/libogc. "
                        "Please install libogc from devkitPro.")
  endif()
endif()

# Build options
if(WII_BUILD)
    # Force OpenGL on Wii (OpenGX) and disable Editor by default
    option(WITH_OPENGL "Build with OpenGL support" ON)
    option(WITH_EDITOR "Build with level editor support" OFF)
else()
    option(WITH_OPENGL "Build with OpenGL support" ON)
    option(WITH_EDITOR "Build with level editor support" OFF)
endif()

option(BUILD_TESTS "Build test programs" OFF)
option(ENABLE_LOGGING "Enable application logging" OFF)

# Compiler Warning Options
option(WARNINGS "Enable extra compiler warnings (-Wall -Wextra)" ON)
option(WERROR "Treat compiler warnings as errors (-Werror)" OFF)

# Add module path for custom Find modules, toolchains, and platform files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Find required packages
find_package(PkgConfig REQUIRED)

# SDL2 and related libraries
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

# Wii Specific Libraries
if(WII_BUILD)
    # Define search paths for Wii libraries to support both local and system toolchains
    set(DKP_LIBOGC_PATH "$ENV{DEVKITPRO}/libogc/lib/wii")
    set(DKP_PORTLIBS_PATH "$ENV{DEVKITPRO}/portlibs/wii/lib")

    # We use HINTS to tell CMake where to look.
    # libfat, wiiuse, and bte are core libs located in libogc/lib/wii
    find_library(OGC_LIB ogc HINTS ${DKP_LIBOGC_PATH} REQUIRED)
    find_library(FAT_LIB fat HINTS ${DKP_LIBOGC_PATH} REQUIRED)
    find_library(WIIUSE_LIB wiiuse HINTS ${DKP_LIBOGC_PATH} REQUIRED)
    find_library(BTE_LIB bte HINTS ${DKP_LIBOGC_PATH} REQUIRED)
    
    # opengx is a portlib located in portlibs/wii/lib
    find_library(OPENGX_LIB opengx HINTS ${DKP_PORTLIBS_PATH} REQUIRED)
    
    message(STATUS "Found Wii Libs: ${OGC_LIB}")
    
    # Explicitly add libogc includes (Critical for wiiuse/wpad.h)
    include_directories($ENV{DEVKITPRO}/libogc/include)
endif()

# OpenGL (optional)
if(WITH_OPENGL)
    set(OpenGL_GL_PREFERENCE LEGACY)
    
    if(WII_BUILD)
        # On Wii, we use OpenGX which provides standard GL symbols
        set(OPENGL_FOUND TRUE)
        set(HAVE_OPENGL 1)
        message(STATUS "OpenGL support: enabled (OpenGX)")
    else()
        find_package(OpenGL)
        if(OPENGL_FOUND)
            set(HAVE_OPENGL 1)
            message(STATUS "OpenGL support: enabled")
        else()
            message(STATUS "OpenGL support: disabled (not found)")
            set(WITH_OPENGL OFF)
        endif()
    endif()
else()
    message(STATUS "OpenGL support: disabled")
endif()


# Compile definitions
add_compile_definitions(
    VERSION="${PROJECT_FULL_VERSION}"
    _GNU_SOURCE=1
)

if(HAVE_OPENGL)
    add_compile_definitions(HAVE_OPENGL=1)
endif()

if(NOT WITH_EDITOR)
    add_compile_definitions(DISABLE_EDITOR=1)
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

if(WII_BUILD)
    include_directories($ENV{DEVKITPRO}/libogc/include)
endif()

# Gather all Pingus source files
file(GLOB_RECURSE PINGUS_SOURCES
    "${CMAKE_SOURCE_DIR}/src/editor/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/engine/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/lisp/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/math/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/pingus/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/util/*.cpp"
)

# Exclude main.cpp from library sources (but not pingus_main.cpp!)
list(FILTER PINGUS_SOURCES EXCLUDE REGEX ".*/src/main\\.cpp$")

# Remove optional sources that shouldn't be included by default
list(FILTER PINGUS_SOURCES EXCLUDE REGEX ".*/opengl/.*")

# Remove editor sources if disabled
if(NOT WITH_EDITOR)
    list(FILTER PINGUS_SOURCES EXCLUDE REGEX ".*/src/editor/.*")
endif()

# Add back optional sources based on configuration
if(WITH_OPENGL)
    file(GLOB OPENGL_SOURCES "${CMAKE_SOURCE_DIR}/src/engine/display/opengl/*.cpp")
    list(APPEND PINGUS_SOURCES ${OPENGL_SOURCES})
endif()


# Add Wii specific sources
if(WII_BUILD)
    list(APPEND PINGUS_SOURCES "${CMAKE_SOURCE_DIR}/src/util/wii.cpp")
endif()

# Windows-specific sources (Icon)
if(WIN32)
    list(APPEND PINGUS_SOURCES "${CMAKE_SOURCE_DIR}/packaging/windows/pingus.rc")
endif()

# Create static library
add_library(libpingus STATIC
    ${PINGUS_SOURCES}
)

# Apply compiler warnings if enabled
if(WARNINGS)
    target_compile_options(libpingus PRIVATE -Wall -Wextra)
endif()

if(WERROR)
    target_compile_options(libpingus PRIVATE -Werror)
endif()

if(ENABLE_LOGGING)
    target_compile_definitions(libpingus PRIVATE LOGGING_ENABLED)
endif()

# Set library name (without 'lib' prefix duplication)
set_target_properties(libpingus PROPERTIES OUTPUT_NAME pingus)

# Link libraries for libpingus
target_link_libraries(libpingus
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Link Standard C++ Filesystem (Plain signature to match above)
target_link_libraries(libpingus stdc++fs)

if(WITH_OPENGL AND OPENGL_FOUND)
    if(WII_BUILD)
        target_link_libraries(libpingus ${OPENGX_LIB})
    else()
        target_link_libraries(libpingus ${OPENGL_LIBRARIES})
    endif()
endif()


if(WII_BUILD)
    target_link_libraries(libpingus 
        ${FAT_LIB} 
        ${WIIUSE_LIB} 
        ${BTE_LIB} 
        ${OGC_LIB} 
        m
    )
endif()

# Main executable
add_executable(pingus src/main.cpp)
target_link_libraries(pingus libpingus)
if(NOT WII_BUILD)
    set_target_properties(pingus PROPERTIES OUTPUT_NAME pingus-wii)
endif()

# Generate a linker map file for Wii builds.
# When the Wii exception screen shows a crash address, search pingus.map for
# the nearest address <= that value to identify the function.  The map file
# stays in the build directory and is not distributed.
if(WII_BUILD)
    target_link_options(pingus PRIVATE -Wl,-Map,${CMAKE_CURRENT_BINARY_DIR}/pingus.map)
endif()

# Post-Build Steps
if(WII_BUILD)
    # Strip the ELF binary (Release builds only) to reduce file size
    if(CMAKE_BUILD_TYPE STREQUAL "Release" AND CMAKE_STRIP)
        add_custom_command(TARGET pingus POST_BUILD
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:pingus>
            COMMENT "Stripping ELF binary..."
            VERBATIM
        )
    endif()
    
    # Convert ELF to DOL
    add_custom_command(TARGET pingus POST_BUILD
        COMMAND $ENV{DEVKITPRO}/tools/bin/elf2dol 
                $<TARGET_FILE:pingus>
                ${CMAKE_CURRENT_BINARY_DIR}/boot.dol
        COMMENT "Converting ELF to DOL for Homebrew Channel..."
        VERBATIM
    )
else()
    # Strip the binary in Release mode
    if(CMAKE_BUILD_TYPE STREQUAL "Release" AND CMAKE_STRIP)
        add_custom_command(TARGET pingus POST_BUILD
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:pingus>
            COMMENT "Stripping binary..."
            VERBATIM
        )
    endif()
endif()

# Install targets (Skip for Wii, its files are copied to the SD card by hand)
if(NOT WII_BUILD)
    set(INSTALL_SUBDIR_BIN "games" CACHE STRING "Installation subdir for the binary")
    set(INSTALL_SUBDIR_SHARE "share/games/pingus-wii" CACHE STRING "Installation subdir for data")

    # Where the game looks for its data: the source tree, then the install
    file(RELATIVE_PATH INSTALL_DATA_FROM_BIN "/${INSTALL_SUBDIR_BIN}" "/${INSTALL_SUBDIR_SHARE}")
    target_compile_definitions(libpingus PRIVATE
        BUILD_DATA_DIR="${CMAKE_SOURCE_DIR}/data"
        INSTALL_DATA_FROM_BIN="${INSTALL_DATA_FROM_BIN}")

    install(TARGETS pingus DESTINATION ${INSTALL_SUBDIR_BIN})
    install(DIRECTORY data/ DESTINATION ${INSTALL_SUBDIR_SHARE})

    # Install desktop entry and icon (Linux)
    if(UNIX AND NOT APPLE)
        install(FILES packaging/linux/pingus-wii.desktop DESTINATION share/applications)
        install(FILES data/images/icons/pingus.svg DESTINATION share/icons/hicolor/scalable/apps
                RENAME pingus-wii.svg)
    endif()
endif()

# Build tests if enabled
if(BUILD_TESTS)
    file(GLOB TEST_SOURCES 
        "${CMAKE_SOURCE_DIR}/test/*_test.cpp" 
        "${CMAKE_SOURCE_DIR}/test/*_util.cpp"
    )
    foreach(test_source ${TEST_SOURCES})
        get_filename_component(test_name ${test_source} NAME_WE)
        add_executable(${test_name} ${test_source})
        target_link_libraries(${test_name} libpingus)
    endforeach()
endif()

# Print configuration summary
message(STATUS "")
message(STATUS "Pingus Configuration Summary:")
message(STATUS "  Version: ${VERSION}")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
if(WII_BUILD)
    message(STATUS "  Platform: Nintendo Wii")
    message(STATUS "  Renderer: OpenGX (Hardware Accelerated)")
    message(STATUS "  Output: build/apps/pingus/ (Homebrew Channel)")
else()
    message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
    message(STATUS "  Distribution: build/dist/pingus/")
endif()
message(STATUS "")
message(STATUS "Feature Support:")
message(STATUS "  Logging support: ${ENABLE_LOGGING}")
message(STATUS "  Level Editor: ${WITH_EDITOR}")
message(STATUS "  OpenGL support: ${WITH_OPENGL}")
message(STATUS "  Extra Warnings: ${WARNINGS}")
message(STATUS "  Warnings as Errors: ${WERROR}")
message(STATUS "")
message(STATUS "Optional Builds:")
message(STATUS "  Build tests: ${BUILD_TESTS}")
message(STATUS "")

# EOF
