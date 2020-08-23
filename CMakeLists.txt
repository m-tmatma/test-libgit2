cmake_minimum_required(VERSION 3.12)

set(project_name "test-commit_parsing")
project(${project_name})
add_executable(${project_name} commit_parsing.cpp)
add_subdirectory(libgit2)

# https://cmake.org/cmake/help/v3.0/variable/PROJECT-NAME_SOURCE_DIR.html
# https://cmake.org/cmake/help/v3.0/manual/cmake-variables.7.html
target_include_directories(${project_name} PRIVATE ${libgit2_SOURCE_DIR}/include)
target_link_libraries(${project_name} PRIVATE git2)
