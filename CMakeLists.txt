cmake_minimum_required(VERSION 3.30)
project(2024)

set(CMAKE_CXX_STANDARD 23)

add_executable(2024 main.cpp
        Helpers.h
        Point.h
        Day1/Day1.h
        Day1/Part1.cpp
        Day1/Part2.cpp)
