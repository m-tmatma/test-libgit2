cmake_minimum_required(VERSION 3.12)

set(project_name  "test-libgit2")
set(project_name1 "test-commit_parsing")
set(project_name2 "revwalking")
project(${project_name})
add_executable(${project_name1} commit_parsing.cpp)
add_executable(${project_name2} revwalking.cpp)
add_subdirectory(libgit2)

# https://cmake.org/cmake/help/v3.0/variable/PROJECT-NAME_SOURCE_DIR.html
# https://cmake.org/cmake/help/v3.0/manual/cmake-variables.7.html
target_include_directories(${project_name1} PRIVATE ${libgit2_SOURCE_DIR}/include)
target_link_libraries(${project_name1} PRIVATE git2)

target_include_directories(${project_name2} PRIVATE ${libgit2_SOURCE_DIR}/include)
target_link_libraries(${project_name2} PRIVATE git2)
