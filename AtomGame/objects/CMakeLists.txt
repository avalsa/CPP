cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Player.cpp Player.h
        Bot.cpp Bot.h
        PhysicalObject.cpp PhysicalObject.h
        CustomObject.cpp CustomObject.h
        Teleporter.cpp Teleporter.h
        TransMapTeleporter.cpp TransMapTeleporter.h
        Coin.cpp Coin.h
        Actor.h Actor.cpp
        Weapon.cpp Weapon.h
        Bullet.cpp Bullet.h)

add_subdirectory(VCPU)
link_libraries(vcpu)
link_libraries(tinyxml2)
add_library(Objects STATIC ${SOURCE_FILES})