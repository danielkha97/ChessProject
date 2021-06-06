cmake_minimum_required(VERSION 3.19)
project(finalProject C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(finalProject
        common.c
        common.h
        main.c
        Q1.c
        Q1.h
        Q2.c
        Q2.h
        Q3.c
        Q3.h
        Q4.c
        Q4.h
        Q5.c
        Q5.h)
