cmake_minimum_required(VERSION 3.5)

add_library(maze base gen_algs)

add_executable(bin_tree_demo bin_tree_demo)
target_link_libraries(bin_tree_demo maze) 
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -pg -O0")


# tests tests tests, keep them in the same place as the source
enable_testing()
add_executable(test_maze base_test)
target_link_libraries(test_maze maze gtest) 
add_test(test_maze ${CMAKE_CURRENT_BINARY_DIR}/test_maze)
