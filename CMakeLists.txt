cmake_minimum_required(VERSION 3.21)
project(STP)

set(CMAKE_CXX_STANDARD 20)

add_executable(STP main.cpp)
add_executable(EX1 exercise1.cpp)
add_executable(EX2 exercise2.cpp benchmark.cpp benchmark.h lehmer.cpp lehmer.h)