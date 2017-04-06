cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Mechanics.cpp Mechanics.h main.cpp)

add_executable(Game ${SOURCE_FILES})

target_link_libraries(Game Objects)
target_link_libraries(Game Graphics)