cmake_minimum_required(VERSION 3.10)

# Define your project and set the C++ standard
project(FattyHelper VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(imgui)  # ImGui headers
# Your own project include directory (if you have)

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
        src/Game.h
        src/Game.cpp
        src/FileHandler.cpp
        src/FileHandler.h
        src/TextDisplay.cpp
        src/TextDisplay.h
)


# Find SDL2 on the system
set(CMAKE_PREFIX_PATH "C:/Libraries/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Define the executable target
add_executable(FattyHelper ${SOURCES})


# Link SDL2 libraries to your executable
target_link_libraries(FattyHelper ${SDL2_LIBRARIES} SDL2::SDL2main)
