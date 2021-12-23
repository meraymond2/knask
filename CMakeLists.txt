cmake_minimum_required(VERSION 3.21)
project(knask)

set(CMAKE_CXX_STANDARD 17)

add_executable(knask main.cpp parser.cpp parser.h bytes.h bytes.cpp)
