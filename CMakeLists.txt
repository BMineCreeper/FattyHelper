cmake_minimum_required(VERSION 3.10)
project(FattyHelper VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Depencencies
include(FetchContent)

FetchContent_Declare(
  SDL2_Image 
  URL https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.8.2.tar.gz
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(SDL2_Image)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(imgui)

set(SOURCES
        src/main.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_sdl2.cpp
        imgui/backends/imgui_impl_sdlrenderer2.cpp
        src/SetupUtils.h
        src/Editor.h
        src/Editor.cpp
        src/FileHandler.h
        src/TextDisplay.h
        src/AttackHandler.h
        src/AttackHandler.cpp
)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(FattyHelper ${SOURCES})
target_link_libraries(FattyHelper PRIVATE SDL2::SDL2 SDL2_image)
