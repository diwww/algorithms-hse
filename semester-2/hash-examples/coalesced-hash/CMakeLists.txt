cmake_minimum_required(VERSION 3.6)
project(coalesced_hash)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp hashtable.h hashtable.hpp)
add_executable(coalesced_hash ${SOURCE_FILES})