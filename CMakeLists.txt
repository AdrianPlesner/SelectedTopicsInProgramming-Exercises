cmake_minimum_required(VERSION 3.21)
project(STP)

set(CMAKE_CXX_STANDARD 20)

add_executable(STP main.cpp)
add_executable(EX1 exercise1.cpp)
add_executable(EX2 exercise2.cpp benchmark.cpp benchmark.h lehmer.cpp lehmer.h)
add_executable(EX3 exercise3.cpp)
add_executable(SS1 main.cpp NumberSeries.cpp NumberSeries.h benchmark.cpp benchmark.h dynamic_NumberSeries.cpp dynamic_NumberSeries.h)
add_executable(EX5 exercise5.cpp Base.cpp Base.h Derived.cpp Derived.h benchmark.h benchmark.cpp)
add_executable(EX7 exercise7.cpp)


option(UBSAN "Undefined Behavior Sanitizer")
option(ASAN "Address Sanitizer")

if (UBSAN)
    message(STATUS "Enabling Undefined Behavior Sanitizer")
    add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=undefined)
endif(UBSAN)

if (ASAN)
    message(STATUS "Enabling Address Sanitizer")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif(ASAN)

add_executable(test_polygon test_polygon.cpp polygon.cpp)