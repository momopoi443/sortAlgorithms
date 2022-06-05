cmake_minimum_required(VERSION 3.21)
project(Sort_Array)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Sort_Array
        main.cpp
        sortAlgorithms/sortAlgorithms.cpp sortAlgorithms/sortAlgorithms.h)
