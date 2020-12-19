cmake_minimum_required(VERSION 3.10)

# CXX config
set(CMAKE_CXX_STANDARD 17)

# Add sources
FILE(GLOB CoreUiSources "src/ui/*.cpp")
FILE(GLOB CoreEngineSources "src/engine/*.cpp")
FILE(GLOB CoreGraphicsSources "src/graphics/*.cpp")
FILE(GLOB CoreIoSources "src/io/*.cpp")


# create core lib
add_library(planecontrol_core ${CoreUiSources} ${CoreEngineSources} ${CoreGraphicsSources} ${CoreIoSources})

find_package(PNG REQUIRED)
target_link_libraries(planecontrol_core ${PNG_LIBRARY})

# set include directory
include_directories(planecontrol_core "include" "ext" ${PNG_INCLUDE_DIR})
