cmake_minimum_required(VERSION 3.15)
project(LI2 C)

set(CMAKE_C_STANDARD 99)

add_executable(LI2 main.c dados.c dados.h interface.c interface.h logica.c logica.h)