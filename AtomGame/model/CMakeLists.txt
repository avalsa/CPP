cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS " -pthread")

set(SOURCE_FILES Model.cpp Model.h)

add_library(Mechanics STATIC ${SOURCE_FILES})

target_link_libraries(Mechanics Objects)