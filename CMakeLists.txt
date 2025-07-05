cmake_minimum_required(VERSION 4.0.3)

set(CMAKE_CXX_STANDARD 11)

project(Minesweeper VERSION 1.0)

find_package(SDL2 REQUIRED)
file(GLOB sources Class/*.cpp Class/TinyXML/*.cpp)

add_executable(Minesweeper main.cpp ${sources})

target_include_directories(Minesweeper PRIVATE Class)
target_link_libraries(Minesweeper SDL2 SDL2main SDL2_image)