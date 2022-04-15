cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(vector)

add_executable(test src/test.cpp)

target_include_directories(test PUBLIC include)