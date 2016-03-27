cmake_minimum_required(VERSION 3.5)
project (mazes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -std=c++11 -m64")

find_package(GTest)
enable_testing()

add_subdirectory(src)

