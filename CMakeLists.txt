cmake_minimum_required(VERSION 3.14)
project(Rotacja3D VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(WEKTOR ./inc/Wektor.hpp src/empty.cpp)
target_include_directories(WEKTOR PUBLIC ./inc ./src ./fml)

add_library(MACIERZ ./src/Macierz.cpp)
target_link_libraries(MACIERZ WEKTOR)
target_include_directories(MACIERZ PUBLIC ./inc ./src ./fml)

add_library(PROSTOPADLOSCIAN ./src/Prostopadloscian.cpp)
target_link_libraries(PROSTOPADLOSCIAN MACIERZ)
target_include_directories(PROSTOPADLOSCIAN PUBLIC ./inc ./src)

add_library(GNUPLOT ./src/gnuplot.cpp)
target_include_directories(GNUPLOT PUBLIC ./inc)

set(LIBS WEKTOR MACIERZ PROSTOPADLOSCIAN GNUPLOT)

add_executable(Rotacja3D ./src/_main.cpp)
target_link_libraries(Rotacja3D ${LIBS})

target_compile_options(Rotacja3D PUBLIC -Wall -Wextra -pedantic -Werror)