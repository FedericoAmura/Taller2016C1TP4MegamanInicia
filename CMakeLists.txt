cmake_minimum_required(VERSION 3.5)
project(Megaman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -g -O0 -pthread" )

set(SOURCE_FILES main.cpp)
add_executable(Megaman ${SOURCE_FILES})