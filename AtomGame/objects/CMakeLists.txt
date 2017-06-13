cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Player.cpp Actor.h Actor.cpp GameObject.h Player.h Weapon.h Bot.cpp Bot.h PhysicalObject.cpp PhysicalObject.h CustomObject.cpp CustomObject.h Teleporter.cpp Teleporter.h TransMapTeleporter.cpp TransMapTeleporter.h Coin.cpp Coin.h)

add_subdirectory(VCPU)
link_libraries(vcpu)
link_libraries(tinyxml2)
add_library(Objects STATIC ${SOURCE_FILES})