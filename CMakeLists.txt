cmake_minimum_required(VERSION 3.10)

# CXX config
set(CMAKE_CXX_STANDARD 20)

# set the project name
project(planecontrol)

add_executable(${PROJECT_NAME} src/main.cpp)
include_directories(planecontrol include)

# internal dependencies
target_link_libraries(${PROJECT_NAME} planecontrol_core)
add_subdirectory(src/core)

# other lib dependencies
find_package(SDL2 REQUIRED)
include_directories(planecontrol ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
