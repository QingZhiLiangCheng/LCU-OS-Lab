cmake_minimum_required(VERSION 3.22)
project(lcuOsLab)

set(CMAKE_CXX_STANDARD 17)

add_executable(lcuOsLab lab1/HPF.c
        lab1/HPF_optimization.cpp
        lab1/RR.cpp
)
