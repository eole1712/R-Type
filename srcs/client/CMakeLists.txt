cmake_minimum_required(VERSION 2.6)
project(RType)

project(MonsterTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)
set(EXECUTABLE_OUTPUT_PATH .. )
set(LIBRARY_OUTPUT_PATH ../../../libs/client/ )

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(rtype_VERSION_MAJOR 1)
set(rtype_VERSION_MINOR 0)

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "rtype")
include_directories(BEFORE core)
include_directories(BEFORE graphics)
include_directories(BEFORE network)
include_directories(BEFORE unit)
include_directories(BEFORE unit/monsters)
include_directories(BEFORE misc)
include_directories(BEFORE ../misc)
include_directories(BEFORE ../common/)
include_directories(BEFORE ../misc/network)

add_executable(${EXECUTABLE_NAME}
	core/main.cpp 
	core/Menu.cpp 
	core/Player.cpp 
	core/Game.cpp
	core/Client.cpp
	unit/AUnit.cpp
	unit/UnitFactory.cpp
	graphics/Animation.cpp 
	graphics/ClickableBtn.cpp 
	graphics/Editable.cpp 
	graphics/GameListItem.cpp

	network/NetClient.cpp
	../misc/network/Networker.cpp
	../misc/network/UdpSocket.cpp
	../misc/network/NetManager.cpp
	../misc/APacket.cpp
	../misc/ClientConnexionPacket.cpp
	../misc/ClientGameConnectPacket.cpp
	../misc/ClientGameInfoPacket.cpp
	../misc/ClientKeyboardPressPacket.cpp
	../misc/ServerConnexionPacket.cpp
	../misc/ServerPlayerMovePacket.cpp
	../misc/ServerGameConnectPacket.cpp
	../misc/ServerTimerRefreshPacket.cpp
	../misc/ServerGameInfoPacket.cpp
	../misc/ServerUnitDiePacket.cpp
	../misc/ServerPingPacket.cpp
	../misc/ServerUnitSpawnPacket.cpp

	../common/linux_specific/CULibLoader.cpp

	misc/Time.cpp 
	../misc/Lock.cpp)

if (APPLE)
   set(CMAKE_MACOSX_RPATH ON)
   set(CMAKE_SKIP_BUILD_RPATH FALSE)
   set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
   set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
   set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
   list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
   if("${isSystemDir}" STREQUAL "-1")
      set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
   endif()
endif(APPLE)

add_library(MonsterTest SHARED unit/monsters/MonsterTest.cpp unit/AUnit.cpp graphics/Animation.cpp 
)

if (WIN32)
   include_directories(BEFORE ../common/windows_specific)
else()
   target_link_libraries(${EXECUTABLE_NAME} -lpthread)
   target_link_libraries(${EXECUTABLE_NAME} -ldl)
   include_directories(BEFORE ../common/linux_specific)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})

# Detect and add SFML
find_package(SFML 2.1 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
