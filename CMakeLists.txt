cmake_minimum_required(VERSION 3.5)
project(Megaman)

#Esto setea que compile en bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#Magia para que ande gtkmm
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

#Aca van todos los flags del compilador
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -g -O0 -pthread" )

#Mas magia
link_directories( ${GTKMM_LIBRARY_DIRS}  )
include_directories( ${GTKMM_INCLUDE_DIRS}  )

#Dependencias, agregar archivos en el ejecutable pertinente solamente
set(SOURCE_FILES editor/main.cpp)
add_executable(editor ${SOURCE_FILES})

set(SOURCE_FILES client/main.cpp)
add_executable(client ${SOURCE_FILES})

set(SOURCE_FILES server/main.cpp)
add_executable(server ${SOURCE_FILES})

#fin de la magia
target_link_libraries(editor ${GTKMM_LIBRARIES} )