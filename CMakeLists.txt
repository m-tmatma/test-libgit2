cmake_minimum_required(VERSION 3.6)
project (test-libgit2)

add_subdirectory(libgit2)

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp ${CMAKE_CURRENT_LIST_DIR}/*.h)
include_directories(${libgit2_SOURCE_DIR}/include)

add_executable(test-libgit2 ${SRC})
target_link_libraries(test-libgit2 git2)
