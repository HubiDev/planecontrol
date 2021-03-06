cmake_minimum_required(VERSION 3.10)

# CXX config
set(CMAKE_CXX_STANDARD 17)

# compile flags
SET(GCC_PROF_COMPILE_FLAGS "-g")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_PROF_COMPILE_FLAGS}")

# set the project name
project(planecontrol)

add_executable(${PROJECT_NAME} src/main.cpp)
include_directories(planecontrol src/game/include src/core/include /usr/local/include)

# internal dependencies
target_link_libraries(${PROJECT_NAME} planecontrol_core)
add_subdirectory(src/core)

target_link_libraries(${PROJECT_NAME} planecontrol_game)
add_subdirectory(src/game)

# other lib dependencies
find_package(SDL2 REQUIRED)
find_package(OpenGL)
find_package(PNG REQUIRED)
include_directories(${PROJECT_NAME} ${PNG_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY} ${PNG_LIBRARY})

# copy resources to execution directory
file(COPY resources/textures DESTINATION resources)
file(COPY resources/levels DESTINATION resources)
