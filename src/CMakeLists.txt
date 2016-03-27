cmake_minimum_required(VERSION 3.5)

add_library(maze base)

# tests tests tests, keep them in the same place as the source
enable_testing()
add_executable(test_maze base_test)
target_link_libraries(test_maze maze gtest) 
add_test(test_maze ${CMAKE_CURRENT_BINARY_DIR}/test_maze)
