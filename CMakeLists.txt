cmake_minimum_required(VERSION 3.2)
project(Megaman)

#Esto setea que compile en bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#Magia para que ande gtkmm
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

#glog
find_package (glog 0.3.4 REQUIRED)

#box2d
add_subdirectory(Box2D)
include_directories (${Box2D_SOURCE_DIR})

#Aca van todos los flags del compilador
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -g -O0 -pthread " )

#Mas magia
link_directories( ${GTKMM_LIBRARY_DIRS}  )
include_directories( ${GTKMM_INCLUDE_DIRS}  )

#Dependencias, agregar archivos en el ejecutable pertinente solamente
#O usar un ejecutable por carpeta y usar FILE(GLOB var dir/*) (uno solo o hay choque de mains)
set(SOURCE_FILES editor/main.cpp entities.h editor/Level.cpp editor/Level.h editor/Entity.cpp editor/Entity.h
        editor/Layer.cpp editor/Layer.h jsoncpp.cpp editor/Workspace.cpp editor/Workspace.h
        json/json-forwards.h json/json.h editor/ToolboxModelColumns.cpp editor/ToolboxModelColumns.h editor/EntitySet.cpp
        editor/EntitySet.h common/SpriteDispenser.cpp common/SpriteDispenser.h common/Drawing.cpp common/Drawing.h common/Thread.cpp
        common/Thread.h editor/WorkspaceEventManager.cpp editor/WorkspaceEventManager.cpp editor/WorkspaceEventManager.h
        editor/SelectionLabel.cpp editor/SelectionLabel.cpp editor/SelectionLabel.h editor/SelectionDrawing.cpp
        editor/SelectionDrawing.h editor/ButtonDeleteSelection.cpp editor/ButtonDeleteSelection.h editor/Selector.cpp
        editor/Selector.h editor/EntityIconView.cpp editor/EntityIconView.h editor/EditorMainWindow.cpp editor/EditorMainWindow.h
        editor/DynamicLayer.cpp editor/DynamicLayer.h editor/ChamberLevel.cpp editor/ChamberLevel.h editor/EditorApp.cpp editor/EditorApp.h editor/BackgroundComboBox.cpp editor/BackgroundComboBox.h editor/BackgroundImage.cpp editor/BackgroundImage.h)
add_executable(editor ${SOURCE_FILES})

#files comunes
FILE(GLOB COMMON_SOURCE_FILES common/*)

#files client en carpeta client
FILE(GLOB CLIENT_SOURCE_FILES client/*)
#ejecutable client
add_executable(client ${CLIENT_SOURCE_FILES} ${COMMON_SOURCE_FILES})

#files en carpeta server, de forma recursiva(incluye archivos de carpetas adentro de la carpeta)
FILE(GLOB_RECURSE SERVER_SOURCE_FILES server/*)
#ejecutable server
add_executable(server ${SERVER_SOURCE_FILES} ${COMMON_SOURCE_FILES} jsoncpp.cpp json/json-forwards.h json/json.h server/Model/Boss.cpp server/Model/Boss.h server/Model/FlyingEnemy.cpp server/Model/FlyingEnemy.h)

#linkeos
target_link_libraries(editor ${GTKMM_LIBRARIES} )
target_link_libraries(client ${GTKMM_LIBRARIES} )
target_link_libraries (client glog::glog)
target_link_libraries(server ${GTKMM_LIBRARIES} )
target_link_libraries (server glog::glog)
target_link_libraries (server Box2D)
