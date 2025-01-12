cmake_minimum_required(VERSION 3.30)
project(cp)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include
    src/leetcode/util)

add_executable(cp
    src/leetcode/c432/p4.cpp
)
