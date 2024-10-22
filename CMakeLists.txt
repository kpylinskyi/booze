cmake_minimum_required(VERSION 3.10)

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

# Find GTK 4
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

# Include GTK directory
include_directories(${GTK_INCLUDE_DIRS})

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
)

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Executable target
add_executable(booze ${SOURCES})

# Include directories for the target
target_include_directories(booze PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link Boost libraries
target_link_libraries(booze PRIVATE ${Boost_LIBRARIES})

# Compile options
target_compile_options(booze PRIVATE -Wall -Wextra -pedantic)
