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

# find_package(nlohmann_json 3.11.2 REQUIRED)
# target_link_libraries(booze PRIVATE nlohmann_json::nlohmann_json)

# OR

# include(FetchContent)
# FetchContent_Declare(
#   json
#   GIT_REPOSITORY https://github.com/nlohmann/json.git
#   GIT_TAG v3.11.2
# )
# FetchContent_MakeAvailable(json)

# Include nlohmann/json directory
# include_directories(${json_SOURCE_DIR}/single_include)

# Source files
set(SOURCES
    src/main.cpp
    src/core/cmd/cmd.cpp
    src/core/pkg.cpp         # Add the source file where Package is implemented
    src/core/tasks.cpp
    src/logger/logger.cpp
    src/logger/log_factory.cpp
    src/logger/log_level.cpp
    src/logger/log/log.cpp
    src/logger/log/info_log.cpp
    src/logger/log/error_log.cpp
    src/logger/log/warning_log.cpp
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
