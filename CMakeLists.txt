cmake_minimum_required(VERSION 3.20)

project(ADC C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(ADC
        main.c
        ADC.c
        io.c
        stats.c
)