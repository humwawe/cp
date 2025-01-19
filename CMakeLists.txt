cmake_minimum_required(VERSION 3.27)
project(cp)

set(CMAKE_CXX_STANDARD 23)

include_directories(
    src/leetcode/util)

add_executable(cp
    src/leetcode/c433/p2.cpp
    #    src/leetcode/c433/p4.cpp
)
