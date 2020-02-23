cmake_minimum_required(VERSION 3.15)
project(sort_download)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(sort_download source/sorter.h main.cpp)
add_executable(example source/sorter.h example/example.cpp)
