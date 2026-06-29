cmake_minimum_required(VERSION 4.2)
project(ADC C)

set(CMAKE_C_STANDARD 99)

add_executable(ADC main.c
        ADC.h
        io.h
        stats.h
        ADC.cpp
        io.cpp)
