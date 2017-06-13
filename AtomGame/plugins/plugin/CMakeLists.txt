cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Plugin.h Plugin.cpp)

add_library(Plugin STATIC ${SOURCE_FILES})