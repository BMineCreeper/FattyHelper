cmake_minimum_required(VERSION 3.10)

# Define your project and set the C++ standard
project(FattyHelper VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path where SDL2 and SDL2_image are installed
set(CMAKE_PREFIX_PATH "C:/Libraries/")

# Include directories for ImGui
include_directories(imgui)

# Source files for your project
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
)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL2_image
find_package(SDL2_image CONFIG REQUIRED)
include_directories("C:\\Libraries\\SDL2_image\\x86_64-w64-mingw32\\include\\SDL2")
# Debugging messages
message(STATUS "SDL2 include dirs: " ${SDL2_INCLUDE_DIRS})
message(STATUS "SDL2_image include dirs: " ${SDL2_IMAGE_INCLUDE_DIRS})

# Add the executable
add_executable(FattyHelper ${SOURCES})

target_link_libraries(FattyHelper "C:\\Libraries\\SDL2_image\\x86_64-w64-mingw32\\lib\\libSDL2_image.a" ${SDL2_LIBRARIES})
