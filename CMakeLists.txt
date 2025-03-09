cmake_minimum_required(VERSION 3.27)
project(cp)

set(CMAKE_CXX_STANDARD 23)

include_directories(
    src/leetcode/util)

add_executable(cp
    src/leetcode/c439/p1.cpp
    src/leetcode/c439/p2.cpp
    src/leetcode/c439/p3.cpp
    src/leetcode/c439/p4.cpp
    src/leetcode/c440/p1.cpp
    src/leetcode/c440/p2.cpp
    src/leetcode/c440/p3.cpp
    src/leetcode/c440/p4.cpp
)
