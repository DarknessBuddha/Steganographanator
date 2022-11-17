cmake_minimum_required(VERSION 3.23)
project(PA2 C)

set(CMAKE_C_STANDARD 17)

add_executable(PA2 driver.c ppm.h ppm.c EncodeDecode.c EncodeDecode.h)
