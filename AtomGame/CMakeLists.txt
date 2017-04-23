cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS " -pthread")

add_subdirectory(objects)
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(controller)
add_subdirectory(tests)

add_custom_target(PROPS SOURCES log4cpp.properties)

set(SOURCE_FILES main.cpp)

add_executable(Run ${SOURCE_FILES})

target_link_libraries(Run log4cpp)
target_link_libraries(Run Objects)
#target_link_libraries(Game sfml-graphics sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_link_libraries(Run Mechanics)
target_link_libraries(Run Graphics)