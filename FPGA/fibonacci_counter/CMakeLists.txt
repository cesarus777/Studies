cmake_minimum_required(VERSION 3.13.4)

project(fibonacci_counter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Quartus REQUIRED)

add_subdirectory(src)
