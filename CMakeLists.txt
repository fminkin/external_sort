cmake_minimum_required(VERSION 3.12)
project(external_sort_project)

set(CMAKE_CXX_STANDARD 14)
include_directories("lib")
add_library(external_sort
  lib/external_sort.cc
  lib/filesystem.cc)

add_executable(external_sort_bin main.cc)
target_link_libraries(external_sort_bin external_sort)