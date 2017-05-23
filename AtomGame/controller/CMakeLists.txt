cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS " -pthread")

set(SOURCE Controller.h Controller.cpp)

add_library(Game STATIC ${SOURCE})

target_link_libraries(Game log4cpp)
target_link_libraries(Game Objects)
target_link_libraries(Game Mechanics)
target_link_libraries(Game Graphics)