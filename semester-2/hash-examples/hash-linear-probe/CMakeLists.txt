cmake_minimum_required(VERSION 3.6)
project(hash_linear_probe)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp hashtable.h hashtable.hpp)
add_executable(hash_linear_probe ${SOURCE_FILES})