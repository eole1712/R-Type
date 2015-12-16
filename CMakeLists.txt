cmake_minimum_required(VERSION 2.6)

project(R-Type)

set(EXECUTABLE_OUTPUT_PATH ../bin/)
set(LIBRARY_OUTPUT_PATH ../libs/server/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

#All include directories
include_directories(
	srcs/server/core
	srcs/server/core/missiles
	srcs/server/core/monsters
	srcs/server/misc
	srcs/server/network
	srcs/misc
	srcs/misc/network
	srcs/common
	)
if (UNIX)
include_directories(
	srcs/common/linux_specific	
	)
endif (UNIX)
if (WIN32)
include_directories(
	srcs/common/windows_specific
	)
endif(WIN32)

#Server sources files
set(server_sources
	srcs/misc/APacket.cpp
	srcs/misc/ClientConnexionPacket.cpp
	srcs/misc/ClientGameConnectPacket.cpp
	srcs/misc/ClientGameInfoPacket.cpp
	srcs/misc/ClientKeyboardPressPacket.cpp
	srcs/misc/Lock.cpp
	srcs/misc/ServerConnexionPacket.cpp
	srcs/misc/ServerGameConnectPacket.cpp
	srcs/misc/ServerGameInfoPacket.cpp
	srcs/misc/ServerPingPacket.cpp
	srcs/misc/ServerPlayerMovePacket.cpp
	srcs/misc/ServerTimerRefreshPacket.cpp
	srcs/misc/ServerUnitDiePacket.cpp
	srcs/misc/ServerUnitSpawnPacket.cpp
	srcs/misc/network/NetManager.cpp
	srcs/misc/network/Networker.cpp
	srcs/misc/network/UdpSocket.cpp
	srcs/server/main.cpp
	srcs/server/core/ABonus.cpp
	srcs/server/core/AMissile.cpp
	srcs/server/core/AMonster.cpp
	srcs/server/core/AUnit.cpp
	srcs/server/core/FactoryUnit.cpp
	srcs/server/core/Game.cpp
	srcs/server/core/Map.cpp
	srcs/server/core/MissileFactory.cpp
	srcs/server/core/MonsterFactory.cpp
	srcs/server/core/MonsterLabel.cpp
	srcs/server/core/MonsterWave.cpp
	srcs/server/core/MonsterWaveManager.cpp
	srcs/server/core/Player.cpp
	srcs/server/core/Score.cpp
	srcs/server/core/ScoreList.cpp
	srcs/server/core/Server.cpp
	srcs/server/core/User.cpp
	srcs/server/misc/Timer.cpp
	srcs/server/network/NetServer.cpp
	)

if (UNIX)
set(server_sources 
	${server_sources}
	srcs/common/linux_specific/CULibLoader.cpp
	)
endif (UNIX)
if (WIN32)
set(server_sources 
	${server_sources}
	srcs/common/windows_specific/CWLibLoader.cpp
	)
endif (WIN32)

add_executable(RType_server ${server_sources})
target_compile_features(RType_server PRIVATE cxx_range_for)
if (UNIX)
  target_link_libraries(RType_server -lpthread)
  target_link_libraries(RType_server -ldl)
endif (UNIX)
#Client sources files
#set(client_sources
#	srcs/client/main.cpp
#	srcs/client/client.cpp
#	)
#add_executable(RType_client client_sources)

add_library(MonsterTest SHARED
  srcs/server/core/monsters/MonsterTest.cpp
  srcs/server/core/AUnit.cpp
  srcs/server/core/AMonster.cpp
  srcs/server/misc/Timer.cpp)

target_compile_features(MonsterTest PRIVATE cxx_range_for)

add_library(BasicMissile SHARED
  srcs/server/core/missiles/BasicMissile.cpp
  srcs/server/core/AUnit.cpp
  srcs/server/core/AMissile.cpp
  srcs/server/core/Game.cpp)

target_compile_features(BasicMissile PRIVATE cxx_range_for)