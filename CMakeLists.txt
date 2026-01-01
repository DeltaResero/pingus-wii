cmake_minimum_required(VERSION 3.10)
project(Pingus VERSION 0.7.7 LANGUAGES CXX)
set(VERSION ${PROJECT_VERSION})

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build options
# Determine default for Linux evdev support
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LINUXEVDEV_DEFAULT ON)
else()
    set(LINUXEVDEV_DEFAULT OFF)
endif()

# Build options
option(WITH_OPENGL "Build with OpenGL support" ON)
option(WITH_XINPUT "Build with XInput support" OFF)
option(WITH_LINUXEVDEV "Build with Linux evdev support" ${LINUXEVDEV_DEFAULT})
option(WITH_WIIMOTE "Build with Wiimote support" OFF)
option(BUILD_TESTS "Build test programs" OFF)
option(BUILD_EXTRA "Build extra utilities" OFF)

# Add module path for custom Find modules and toolchains
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Find required packages
find_package(PkgConfig REQUIRED)

# SDL and related libraries
pkg_check_modules(SDL REQUIRED sdl)
pkg_check_modules(SDL_IMAGE REQUIRED SDL_image)
pkg_check_modules(SDL_MIXER REQUIRED SDL_mixer)
pkg_check_modules(PNG REQUIRED libpng)

# Boost
# Set policy for modern CMake and Boost 1.70+
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

# In Boost 1.69+, System became header-only
# In Boost 1.89, we only need filesystem (system is header-only)
find_package(Boost 1.69 REQUIRED COMPONENTS filesystem)

# Boost.Signals2 is header-only (old Signals was removed)
if(Boost_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")
    message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
endif()

# OpenGL (optional)
if(WITH_OPENGL)
    find_package(OpenGL)
    if(OPENGL_FOUND)
        set(HAVE_OPENGL 1)
        message(STATUS "OpenGL support: enabled")
    else()
        message(STATUS "OpenGL support: disabled (not found)")
        set(WITH_OPENGL OFF)
    endif()
else()
    message(STATUS "OpenGL support: disabled")
endif()

# Linux evdev (optional)
if(WITH_LINUXEVDEV)
    message(STATUS "Linux evdev support: enabled")
    set(HAVE_LINUXEVDEV 1)
else()
    message(STATUS "Linux evdev support: disabled")
endif()

# Wiimote (optional)
if(WITH_WIIMOTE)
    find_library(CWIID_LIBRARY cwiid)
    find_path(CWIID_INCLUDE_DIR cwiid.h)
    if(CWIID_LIBRARY AND CWIID_INCLUDE_DIR)
        set(HAVE_CWIID 1)
        message(STATUS "Wiimote support: enabled")
    else()
        message(STATUS "Wiimote support: disabled (libcwiid not found)")
        set(WITH_WIIMOTE OFF)
    endif()
else()
    message(STATUS "Wiimote support: disabled")
endif()

# XInput (optional)
if(WITH_XINPUT)
    find_package(X11)
    if(X11_FOUND AND X11_Xi_FOUND)
        set(HAVE_XINPUT 1)
        message(STATUS "XInput support: enabled")
    else()
        message(STATUS "XInput support: disabled (Xi library not found)")
        set(WITH_XINPUT OFF)
    endif()
else()
    message(STATUS "XInput support: disabled")
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
    message(FATAL_ERROR "Cannot determine iconv signature")
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

if(HAVE_LINUXEVDEV)
    add_compile_definitions(HAVE_LINUXEVDEV=1)
endif()

if(HAVE_CWIID)
    add_compile_definitions(HAVE_CWIID=1)
endif()

if(HAVE_XINPUT)
    add_compile_definitions(HAVE_XINPUT=1)
endif()

if(HAVE_ICONV_CONST)
    add_compile_definitions(HAVE_ICONV_CONST ICONV_CONST=${ICONV_CONST})
endif()

# Include directories
include_directories(
    ${CMAKE_BINARY_DIR}  # For config.h
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/logmich/include
    ${SDL_INCLUDE_DIRS}
    ${SDL_IMAGE_INCLUDE_DIRS}
    ${SDL_MIXER_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

file(GLOB_RECURSE LOGMICH_SOURCES 
    "${CMAKE_SOURCE_DIR}/external/logmich/src/*.cpp"
)

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
list(FILTER PINGUS_SOURCES EXCLUDE REGEX ".*/evdev/.*")
list(FILTER PINGUS_SOURCES EXCLUDE REGEX ".*/wiimote/.*")
list(FILTER PINGUS_SOURCES EXCLUDE REGEX ".*/xinput/.*")

# Add back optional sources based on configuration
if(WITH_OPENGL)
    file(GLOB OPENGL_SOURCES "${CMAKE_SOURCE_DIR}/src/engine/display/opengl/*.cpp")
    list(APPEND PINGUS_SOURCES ${OPENGL_SOURCES})
endif()

if(WITH_LINUXEVDEV)
    file(GLOB EVDEV_SOURCES "${CMAKE_SOURCE_DIR}/src/engine/input/evdev/*.cpp")
    list(APPEND PINGUS_SOURCES ${EVDEV_SOURCES})
endif()

if(WITH_WIIMOTE)
    file(GLOB WIIMOTE_SOURCES "${CMAKE_SOURCE_DIR}/src/engine/input/wiimote/*.cpp")
    list(APPEND PINGUS_SOURCES ${WIIMOTE_SOURCES})
endif()

if(WITH_XINPUT)
    file(GLOB XINPUT_SOURCES "${CMAKE_SOURCE_DIR}/src/engine/input/xinput/*.cpp")
    list(APPEND PINGUS_SOURCES ${XINPUT_SOURCES})
endif()

# Windows-specific sources (Icon)
if(WIN32)
    list(APPEND PINGUS_SOURCES "${CMAKE_SOURCE_DIR}/src/win32/pingus.rc")
endif()

# Create static library
add_library(libpingus STATIC
    ${PINGUS_SOURCES}
    ${LOGMICH_SOURCES}
)

# Set library name (without 'lib' prefix duplication)
set_target_properties(libpingus PROPERTIES OUTPUT_NAME pingus)

# Link libraries for libpingus
target_link_libraries(libpingus
    ${SDL_LIBRARIES}
    ${SDL_IMAGE_LIBRARIES}
    ${SDL_MIXER_LIBRARIES}
    ${PNG_LIBRARIES}
    ${Boost_LIBRARIES}
)

if(WITH_OPENGL AND OPENGL_FOUND)
    target_link_libraries(libpingus ${OPENGL_LIBRARIES})
endif()

if(WITH_WIIMOTE AND CWIID_LIBRARY)
    target_link_libraries(libpingus ${CWIID_LIBRARY})
    target_include_directories(libpingus PRIVATE ${CWIID_INCLUDE_DIR})
endif()

if(WITH_XINPUT AND X11_FOUND)
    target_link_libraries(libpingus ${X11_LIBRARIES} ${X11_Xi_LIB})
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

# Install targets
install(TARGETS pingus DESTINATION bin)
install(DIRECTORY data/ DESTINATION share/pingus)

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

# Build extra utilities if enabled
if(BUILD_EXTRA)
    file(GLOB EXTRA_SOURCES "${CMAKE_SOURCE_DIR}/extra/*.cpp")
    foreach(extra_source ${EXTRA_SOURCES})
        get_filename_component(extra_name ${extra_source} NAME_WE)
        add_executable(${extra_name} ${extra_source})
        target_link_libraries(${extra_name} libpingus)
    endforeach()
endif()

# Print configuration summary
message(STATUS "")
message(STATUS "Pingus Configuration Summary:")
message(STATUS "  Version: ${VERSION}")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
message(STATUS "Feature Support:")
message(STATUS "  OpenGL support: ${WITH_OPENGL}")
message(STATUS "  XInput support: ${WITH_XINPUT}")
message(STATUS "  Linux evdev support: ${WITH_LINUXEVDEV}")
message(STATUS "  Wiimote support: ${WITH_WIIMOTE}")
message(STATUS "")
message(STATUS "Optional Builds:")
message(STATUS "  Build tests: ${BUILD_TESTS}")
message(STATUS "  Build extra: ${BUILD_EXTRA}")
message(STATUS "")
