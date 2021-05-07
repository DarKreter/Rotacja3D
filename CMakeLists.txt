cmake_minimum_required(VERSION 3.7)
project(Rotacja3D VERSION 1.0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(WEKTOR ./inc/Wektor.hpp src/empty.cpp)
target_include_directories(WEKTOR PUBLIC ./inc ./src ./fml)

add_library(MACIERZ ./src/Macierz.cpp)
target_link_libraries(MACIERZ WEKTOR)
target_include_directories(MACIERZ PUBLIC ./inc ./src ./fml)

add_library(FIGURE src/Figure.cpp)
target_link_libraries(FIGURE MACIERZ)
target_include_directories(FIGURE PUBLIC ./inc ./src)

add_library(GNUPLOT ./src/gnuplot.cpp)
target_include_directories(GNUPLOT PUBLIC ./inc)

add_library(SCENE ./src/Scene.cpp)
target_link_libraries(FIGURE GNUPLOT)
target_include_directories(SCENE PUBLIC ./inc ./fml)

set(LIBS WEKTOR MACIERZ FIGURE GNUPLOT SCENE)

add_executable(Rotacja3D ./src/_main.cpp src/Scene.cpp inc/Scene.hpp)
target_link_libraries(Rotacja3D ${LIBS})

target_compile_options(Rotacja3D PUBLIC -Wall -Wextra -pedantic)