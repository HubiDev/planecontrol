cmake_minimum_required(VERSION 3.10)

# CXX config
set(CMAKE_CXX_STANDARD 17)

# Add sources
FILE(GLOB CoreUiSources "src/ui/*.cpp")
FILE(GLOB CoreEngineSources "src/engine/*.cpp")
FILE(GLOB CoreGraphicsSources "src/graphics/*.cpp")
FILE(GLOB CoreImageSources "src/image/*.cpp")


# create core lib
add_library(planecontrol_core ${CoreUiSources} ${CoreEngineSources} ${CoreGraphicsSources} ${CoreImageSources})

# set include directory
include_directories(planecontrol_core "include")
