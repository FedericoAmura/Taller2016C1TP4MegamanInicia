cmake_minimum_required(VERSION 3.5)
project(Megaman)

#Esto setea que compile en bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#Magia para que ande gtkmm
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

#glog
set(glog_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glog" )
find_package (glog 0.3.4 REQUIRED)

#Aca van todos los flags del compilador
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -g -O0 -pthread " )

#Mas magia
link_directories( ${GTKMM_LIBRARY_DIRS}  )
include_directories( ${GTKMM_INCLUDE_DIRS}  )

#Dependencias, agregar archivos en el ejecutable pertinente solamente
set(SOURCE_FILES editor/main.cpp entities.h editor/Level.cpp editor/Level.h editor/Entity.cpp editor/Entity.h editor/Orientation.cpp editor/Orientation.h)
add_executable(editor ${SOURCE_FILES})

set(SOURCE_FILES )
add_executable(client ${SOURCE_FILES})

set(SOURCE_FILES server/server_main.cpp server/server_AcceptConnections.cpp server/server_AcceptConnections.h server/server_Server.cpp server/server_Server.h server/server_ServerSocket.cpp server/server_ServerSocket.h common/common_ClientSocket.cpp common/common_ClientSocket.h common/common_Evento.cpp common/common_Evento.h common/common_Handler.cpp common/common_Handler.h common/common_HandlerCoordinator.cpp common/common_HandlerCoordinator.h common/common_Juego.cpp common/common_Juego.h common/common_Observador.cpp common/common_Observador.h common/common_SendRecvThread.cpp common/common_SendRecvThread.h common/common_Socket.cpp common/common_Socket.h common/common_Thread.cpp common/common_Thread.h)
add_executable(server ${SOURCE_FILES})

set(SOURCE_FILES editor/editor_test.cpp editor/Orientation.cpp editor/Orientation.h editor/Entity.cpp editor/Entity.h editor/Level.h editor/Level.cpp)
add_executable(editor_test ${SOURCE_FILES})

#linkeos
target_link_libraries(editor ${GTKMM_LIBRARIES} )
target_link_libraries (server glog::glog)
