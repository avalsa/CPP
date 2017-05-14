cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Player.cpp Actor.h Actor.cpp GameObject.h Player.h Weapon.h Bot.cpp Bot.h GameField.cpp GameField.h PhysicalObject.cpp PhysicalObject.h ProgrammableObject.cpp ProgrammableObject.h)

add_subdirectory(VCPU)
link_libraries(vcpu)
add_library(Objects STATIC ${SOURCE_FILES})