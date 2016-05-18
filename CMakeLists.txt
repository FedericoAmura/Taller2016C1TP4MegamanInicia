cmake_minimum_required(VERSION 3.5)
project(Megaman)

#Esto setea que compile en bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#Magia para que ande gtkmm
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

#glog
#set(glog_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glog" )
find_package (glog 0.3.4 REQUIRED)
#pkg_check_modules(glog 0.3.4)

#Aca van todos los flags del compilador
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -g -O0 -pthread " )

#Mas magia
link_directories( ${GTKMM_LIBRARY_DIRS}  )
include_directories( ${GTKMM_INCLUDE_DIRS}  )

#Dependencias, agregar archivos en el ejecutable pertinente solamente
#O usar un ejecutable por carpeta y usar FILE(GLOB var dir/*) (uno solo o hay choque de mains)
set(SOURCE_FILES editor/main.cpp entities.h editor/Level.cpp editor/Level.h editor/Entity.cpp editor/Entity.h
        editor/Layer.cpp editor/Layer.h jsoncpp.cpp
        json/json-forwards.h json/json.h)
add_executable(editor ${SOURCE_FILES})

set(SOURCE_FILES editor/editor_test.cpp editor/Entity.cpp editor/Entity.h
        editor/Level.h editor/Level.cpp editor/Layer.cpp editor/Layer.h jsoncpp.cpp json/json-forwards.h
        json/json.h)
add_executable(editor_test ${SOURCE_FILES})

FILE(GLOB CLIENT_SOURCE_FILES client/*)
add_executable(client ${CLIENT_SOURCE_FILES})

FILE(GLOB SERVER_SOURCE_FILES server/*)
add_executable(server ${SERVER_SOURCE_FILES})

#linkeos
target_link_libraries(editor_test ${GTKMM_LIBRARIES} )
target_link_libraries(editor ${GTKMM_LIBRARIES} )
target_link_libraries(client ${GTKMM_LIBRARIES} )
target_link_libraries (server glog::glog)
