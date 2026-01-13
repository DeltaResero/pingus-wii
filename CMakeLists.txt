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
project(Pingus VERSION 0.7.7 LANGUAGES CXX)
set(VERSION ${PROJECT_VERSION})

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect Wii build
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "powerpc" AND CMAKE_SYSTEM_NAME STREQUAL "Generic")
  set(WII_BUILD ON)
  message(STATUS "Configuring for Nintendo Wii")
  add_compile_definitions(__WII__ GEKKO)
else()
  set(WII_BUILD OFF)
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

# Add module path for custom Find modules and toolchains
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Find required packages
find_package(PkgConfig REQUIRED)

# SDL and related libraries
pkg_check_modules(SDL REQUIRED sdl)
pkg_check_modules(SDL_IMAGE REQUIRED SDL_image)
pkg_check_modules(SDL_MIXER REQUIRED SDL_mixer)
pkg_check_modules(PNG REQUIRED libpng)

# Wii Specific Libraries
if(WII_BUILD)
    find_library(OGC_LIB ogc REQUIRED)
    find_library(FAT_LIB fat REQUIRED)
    find_library(OPENGX_LIB opengx REQUIRED)
    find_library(WIIUSE_LIB wiiuse REQUIRED)
    find_library(BTE_LIB bte REQUIRED)
    
    message(STATUS "Found Wii Libs: ${OGC_LIB} ${FAT_LIB} ${OPENGX_LIB}")
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


# Check for iconv
include(CheckCXXSourceCompiles)

# On Linux, iconv is usually in glibc, on other systems it might be a separate library
set(CMAKE_REQUIRED_LIBRARIES "")
check_cxx_source_compiles("
#include <iconv.h>
int main() {
    const char *foo;
    iconv(static_cast<iconv_t>(0), &foo, static_cast<size_t*>(0), 
          static_cast<char**>(0), static_cast<size_t*>(0));
    return 0;
}" ICONV_CONST_CONST)

check_cxx_source_compiles("
#include <iconv.h>
int main() {
    char *foo;
    iconv(static_cast<iconv_t>(0), &foo, static_cast<size_t*>(0), 
          static_cast<char**>(0), static_cast<size_t*>(0));
    return 0;
}" ICONV_CONST_EMPTY)

# If glibc iconv didn't work, try with separate iconv library
if(NOT ICONV_CONST_CONST AND NOT ICONV_CONST_EMPTY)
    set(CMAKE_REQUIRED_LIBRARIES "iconv")
    check_cxx_source_compiles("
#include <iconv.h>
int main() {
    const char *foo;
    iconv(static_cast<iconv_t>(0), &foo, static_cast<size_t*>(0), 
          static_cast<char**>(0), static_cast<size_t*>(0));
    return 0;
}" ICONV_CONST_CONST_LIB)
    
    check_cxx_source_compiles("
#include <iconv.h>
int main() {
    char *foo;
    iconv(static_cast<iconv_t>(0), &foo, static_cast<size_t*>(0), 
          static_cast<char**>(0), static_cast<size_t*>(0));
    return 0;
}" ICONV_CONST_EMPTY_LIB)
    
    if(ICONV_CONST_CONST_LIB)
        set(ICONV_CONST_CONST TRUE)
        set(ICONV_NEEDS_LIB TRUE)
    elseif(ICONV_CONST_EMPTY_LIB)
        set(ICONV_CONST_EMPTY TRUE)
        set(ICONV_NEEDS_LIB TRUE)
    endif()
endif()

if(ICONV_CONST_CONST)
    set(ICONV_CONST "const")
    set(HAVE_ICONV_CONST 1)
    message(STATUS "iconv signature: const char**")
elseif(ICONV_CONST_EMPTY)
    set(ICONV_CONST "")
    set(HAVE_ICONV_CONST 1)
    message(STATUS "iconv signature: char**")
else()
    # On Wii, iconv might be missing or different, but we'll assume char** if detection fails
    if(WII_BUILD)
        set(ICONV_CONST "")
        set(HAVE_ICONV_CONST 1)
        message(STATUS "Wii build: assuming iconv signature char**")
    else()
        message(FATAL_ERROR "Cannot determine iconv signature")
    endif()
endif()

# Set HAVE_SDL (always true for this project)
set(HAVE_SDL 1)

# Generate config.h
configure_file(
    "${CMAKE_SOURCE_DIR}/config.h.in"
    "${CMAKE_BINARY_DIR}/config.h"
)

# Compile definitions
add_compile_definitions(
    VERSION="${VERSION}"
    _GNU_SOURCE=1
    HAVE_SDL=1
)

if(HAVE_OPENGL)
    add_compile_definitions(HAVE_OPENGL=1)
endif()

if(HAVE_ICONV_CONST)
    add_compile_definitions(HAVE_ICONV_CONST ICONV_CONST=${ICONV_CONST})
endif()

if(NOT WITH_EDITOR)
    add_compile_definitions(DISABLE_EDITOR=1)
endif()

# Include directories
include_directories(
    ${CMAKE_BINARY_DIR}  # For config.h
    ${CMAKE_SOURCE_DIR}/src
    ${SDL_INCLUDE_DIRS}
    ${SDL_IMAGE_INCLUDE_DIRS}
    ${SDL_MIXER_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
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
    ${SDL_LIBRARIES}
    ${SDL_IMAGE_LIBRARIES}
    ${SDL_MIXER_LIBRARIES}
    ${PNG_LIBRARIES}
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

# Check if iconv is needed as a separate library (macOS, BSD)
if(ICONV_NEEDS_LIB)
    find_library(ICONV_LIBRARY iconv)
    if(ICONV_LIBRARY)
        target_link_libraries(libpingus ${ICONV_LIBRARY})
        message(STATUS "Linking separate iconv library: ${ICONV_LIBRARY}")
    endif()
else()
    message(STATUS "Using iconv from glibc (no separate library needed)")
endif()

# Main executable
add_executable(pingus src/main.cpp)
target_link_libraries(pingus libpingus)

# Copy data directory (Non-Wii)
if(NOT WII_BUILD)
    add_custom_command(TARGET pingus POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/data"
                "$<TARGET_FILE_DIR:pingus>/data"
        COMMENT "Copying data directory to build output..."
        VERBATIM
    )
endif()

# Install targets (Skip for Wii, we build a custom app structure)
if(NOT WII_BUILD)
    install(TARGETS pingus DESTINATION bin)
    install(DIRECTORY data/ DESTINATION share/pingus)
    
    # Install desktop entry (Linux)
    if(UNIX AND NOT APPLE)
        install(FILES packaging/linux/pingus.desktop DESTINATION share/applications)
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

# Wii Post-Build Steps
if(WII_BUILD)
    # Convert ELF to DOL
    add_custom_command(TARGET pingus POST_BUILD
        COMMAND $ENV{DEVKITPRO}/tools/bin/elf2dol 
                $<TARGET_FILE:pingus>
                ${CMAKE_CURRENT_BINARY_DIR}/boot.dol
        COMMENT "Converting ELF to DOL for Homebrew Channel..."
        VERBATIM
    )
    
    # Create Homebrew Channel structure
    add_custom_command(TARGET pingus POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/apps/pingus
        # Copy binary and data
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/boot.dol ${CMAKE_CURRENT_BINARY_DIR}/apps/pingus/boot.dol
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/apps/pingus/data
        # Copy Homebrew Channel metadata (Icon and XML)
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/packaging/wii/icon.png ${CMAKE_CURRENT_BINARY_DIR}/apps/pingus/icon.png
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/packaging/wii/meta.xml ${CMAKE_CURRENT_BINARY_DIR}/apps/pingus/meta.xml
        COMMENT "Creating Homebrew Channel package in build/apps/pingus/..."
        VERBATIM
    )
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
else()
    message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
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
