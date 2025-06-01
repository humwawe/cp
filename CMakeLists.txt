cmake_minimum_required(VERSION 3.27)
project(cp)

set(CMAKE_CXX_STANDARD 23)

include_directories(
    src/leetcode/util)

add_definitions(-DLC_LOCAL)

add_executable(cp
    src/leetcode/c452/p1.cpp
    src/leetcode/c452/p2.cpp
    src/leetcode/c452/p3.cpp
    src/leetcode/c452/p4.cpp
)
