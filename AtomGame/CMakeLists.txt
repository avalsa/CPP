cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(objects)

add_subdirectory(mechanics)

add_subdirectory(visualization)

add_subdirectory(tests)
