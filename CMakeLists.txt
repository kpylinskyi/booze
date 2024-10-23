cmake_minimum_required(VERSION 3.10)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

project(Booze VERSION 1.0)

# C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enabling static linking for Boost library
set(Boost_USE_STATIC_LIBS ON)

# Find Boost
find_package(Boost 1.70 REQUIRED COMPONENTS process)

# Include Boost directory
include_directories(${Boost_INCLUDE_DIRS})

# Find GTKMM
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Include GTKMM directory
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# Add nlohmann-json
include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# Include nlohmann/json directory
include_directories(${json_SOURCE_DIR}/single_include)

# Source files
set(SOURCES
    src/main.cpp
    src/core/system.cpp
    src/core/package.cpp
    src/core/package_manager.cpp
    src/gui/main_window.cpp
)

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Executable target
add_executable(booze ${SOURCES})

# Include directories for the target
target_include_directories(booze PRIVATE ${PROJECT_SOURCE_DIR}/include ${GTKMM_INCLUDE_DIRS})

# Link Boost libraries
target_link_libraries(booze PRIVATE ${Boost_LIBRARIES} ${GTKMM_LIBRARIES})

# Compile options
target_compile_options(booze PRIVATE -Wall -Wextra -pedantic)
