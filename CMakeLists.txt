cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_DEBUG "-g")


find_package(raylib REQUIRED)

# Collect all source files
file(GLOB_RECURSE SOURCES
    source/*.cc
)

add_executable(game ${SOURCES})
target_link_libraries(game PRIVATE raylib)
