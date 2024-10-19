# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Set CMP0167 to NEW to avoid warning about Boost module removal
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

# Project name and version
project(Booze VERSION 1.0)

# C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Boost (with Boost.Process)
find_package(Boost 1.70 REQUIRED COMPONENTS process)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!")
endif()
include_directories(/usr/local/include)
link_directories(/usr/local/lib)


# Find GTKmm4 (C++ bindings for GTK 4)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${Boost_INCLUDE_DIRS})

# Define your source files
set(SOURCES
    src/main.cpp
)

# Create the executable 'booze' from the source files
add_executable(booze ${SOURCES})

# Link against the Boost and GTKmm libraries
target_link_libraries(booze ${GTKMM_LIBRARIES} ${Boost_LIBRARIES})

# Add GTKmm-specific definitions (if any)
add_definitions(${GTKMM_CFLAGS_OTHER})

# Set compile options (warnings, extra checks)
target_compile_options(booze PRIVATE -Wall -Wextra -pedantic)

if(CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
elseif(CMAKE_OSX_ARCHITECTURES MATCHES "x86_64")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()
