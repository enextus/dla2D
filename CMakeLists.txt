cmake_minimum_required(VERSION 4.3)
project(dla2D C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(dla2D
        bitmaplib.c
        bitmaplib.h
        dla.c
        paulslib.c
        paulslib.h)
