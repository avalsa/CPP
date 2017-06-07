cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        View.cpp View.h
        Animation.cpp Animation.h
        AnimationFactory.cpp AnimationFactory.h
        SpriteFactory.cpp SpriteFactory.h
        )


add_library(Graphics STATIC ${SOURCE_FILES})

target_link_libraries(Graphics Objects)

target_link_libraries(Graphics Game)

target_link_libraries(Graphics sfml-graphics sfml-system sfml-window sfml-graphics sfml-network sfml-audio)