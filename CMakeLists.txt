project(networld LANGUAGES C)
cmake_minimum_required(VERSION 3.10)

# Activate C99 standard:
SET(CMAKE_C_COMPILER "gcc" )
SET(CMAKE_C_FLAGS "-std=c99" )
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# project configuration :
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)

# RayLib:
#find_package(raylib 3.0 REQUIRED)
#set(raylib_VERBOSE 1)

# Local dependency: (RayLib) :
include_directories( ${PROJECT_SOURCE_DIR}/dpd/include )
link_directories( ${PROJECT_SOURCE_DIR}/dpd )

add_executable(risk src/main-viewer.c src/networld.c src/controlpanel.c src/player.c src/random-map.c src/graphical-aspect.c src/window-manager.c src/menu-button.c src/main-menu.c src/int-input.c src/options-menu.c src/mission.c)

target_link_libraries(risk raylib pthread dl rt X11 m)

#without cmake package... 
#include_directories(${PROJECT_SOURCE_DIR}/raylib/src)
#link_directories(${PROJECT_SOURCE_DIR}/raylib)
#target_link_libraries(risk raylib GL m pthread dl rt X11)
