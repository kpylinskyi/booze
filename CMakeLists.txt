# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Booze VERSION 1.0)

# C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Boost (with Boost.Process)
find_package(Boost REQUIRED COMPONENTS process)

# Find GTKmm4 (C++ bindings for GTK 4)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

link_directories(${GTKMM_LIBRARY_DIRS})

set(SOURCES
    src/main.cpp
)

add_executable(booze ${SOURCES})

target_link_libraries(booze ${GTKMM_LIBRARIES} ${Boost_LIBRARIES})

add_definitions(${GTKMM_CFLAGS_OTHER})

target_compile_options(booze PRIVATE -Wall -Wextra -pedantic)
