cmake_minimum_required(VERSION 3.5)
project(Megaman)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -g -O0 -pthread" )

link_directories( ${GTKMM_LIBRARY_DIRS}  )

include_directories( ${GTKMM_INCLUDE_DIRS}  )

set(SOURCE_FILES editor/main.cpp)
add_executable(Editor ${SOURCE_FILES})

set(SOURCE_FILES client/main.cpp)
add_executable(Client ${SOURCE_FILES})

set(SOURCE_FILES server/main.cpp)
add_executable(server ${SOURCE_FILES})

target_link_libraries(Editor ${GTKMM_LIBRARIES} )