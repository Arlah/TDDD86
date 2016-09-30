cmake_minimum_required(VERSION 3.6)
project(labb2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    evilhangman/src/evilhangman.cpp
    wordchain/src/wordchain.cpp)

add_executable(labb2 ${SOURCE_FILES})