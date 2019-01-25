cmake_minimum_required(VERSION 3.6)
project (test-libgit2)

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp ${CMAKE_CURRENT_LIST_DIR}/*.h)
add_executable(test-libgit2 ${SRC})
add_subdirectory(libgit2)
