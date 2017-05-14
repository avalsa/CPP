cmake_minimum_required(VERSION 3.6)
project(AtomGame)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES VCPU.cpp VCPU.h)
add_library(interpreter STATIC ${SOURCE_FILES})