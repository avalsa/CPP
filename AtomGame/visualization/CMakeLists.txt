cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Visualizer.cpp Visualizer.h)

add_library (Graphics ${SOURCE_FILES})

target_link_libraries(Graphics Objects)
