cmake_minimum_required(VERSION 3.7)
project(port_transfer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp serial.cpp serial.h)
add_executable(port_transfer ${SOURCE_FILES})
add_definitions(-Wall -Wextra)
