cmake_minimum_required(VERSION 3.20)

project(celluarAutomataSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(celluarAutomataSim
    src/main.cpp
    src/cell.h
    src/grid.h
    src/grid.cpp
    src/constants.h
)

target_link_libraries(celluarAutomataSim PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)