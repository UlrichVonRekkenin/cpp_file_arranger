cmake_minimum_required(VERSION 3.15)
project(sort_download)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread")

FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(sort_download source/sorter.h main.cpp)
add_executable(example source/sorter.h example/example.cpp)

target_link_libraries(sort_download Boost::program_options)
target_link_libraries(example Boost::program_options)
