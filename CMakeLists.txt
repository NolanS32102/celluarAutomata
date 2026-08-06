cmake_minimum_required(VERSION 3.20)

project(celluarAutomataSim LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

include(FetchContent)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9b
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML ON)
set(BUILD_SHARED_LIBS ON)
FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui-sfml)

add_executable(celluarAutomataSim
    src/main.cpp
    src/cell.h
    src/grid.h
    src/grid.cpp
    src/constants.h
    src/macos_window.h
    src/macos_window.mm
)

target_link_libraries(celluarAutomataSim PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    ImGui-SFML::ImGui-SFML
    "-framework Cocoa"
)
