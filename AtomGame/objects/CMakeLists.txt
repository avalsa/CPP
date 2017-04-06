cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Actor.h GameObject.h Player.cpp Player.h Weapon.h Bot.cpp Bot.h GameField.cpp GameField.h)

add_library (Objects STATIC ${SOURCE_FILES})