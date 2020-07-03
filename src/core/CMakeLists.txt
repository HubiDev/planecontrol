cmake_minimum_required(VERSION 3.10)

# CXX config
set(CMAKE_CXX_STANDARD 17)

# Add sources
FILE(GLOB CoreUiSources "ui/*.cpp")
FILE(GLOB CoreEngineSources "engine/*.cpp")
FILE(GLOB CoreGraphicsSources "graphics/*.cpp")


# create core lib
add_library(planecontrol_core ${CoreUiSources} ${CoreEngineSources} ${CoreGraphicsSources})

# set include directory
include_directories(planecontrol_core "../../include")
