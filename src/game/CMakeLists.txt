cmake_minimum_required(VERSION 3.10)

# CXX config
set(CMAKE_CXX_STANDARD 20)

# Add sources
FILE(GLOB GameElementsSources "elements/*.cpp")

# create core lib
add_library(planecontrol_game ${GameElementsSources} game.cpp)

# linker dependencies
target_link_libraries(planecontrol_game planecontrol_core)

# set include directory
include_directories(planecontrol_game "../../include")
