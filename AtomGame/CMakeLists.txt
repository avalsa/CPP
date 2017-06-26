cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS " -pthread")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_TYPE "Release")


add_subdirectory(objects)
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(controller)
add_subdirectory(tests)
add_subdirectory(plugins/plugin)

add_custom_target(PROPS SOURCES log4cpp.properties)

set(SOURCE_FILES main.cpp)

add_executable(Run ${SOURCE_FILES})

add_library(RToRestart SHARED plugins/RToRestart.cpp plugins/RToRestart.h)

add_library(Rain SHARED plugins/Rain.cpp plugins/Rain.h)

target_link_libraries(Run log4cpp)
target_link_libraries(Run dl)
target_link_libraries(Run Objects)
#target_link_libraries(Game sfml-graphics sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_link_libraries(Run Mechanics)
target_link_libraries(Run Graphics)
target_link_libraries(Run Plugin)

target_link_libraries(RToRestart log4cpp)
target_link_libraries(RToRestart Objects)
target_link_libraries(RToRestart Mechanics)
target_link_libraries(RToRestart Graphics)
target_link_libraries(RToRestart Plugin)

target_link_libraries(Rain log4cpp)
target_link_libraries(Rain Objects)
target_link_libraries(Rain Mechanics)
target_link_libraries(Rain Graphics)
target_link_libraries(Rain Plugin)

build_command(TARGET Run)