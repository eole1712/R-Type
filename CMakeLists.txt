cmake_minimum_required(VERSION 3.1)

project(R-Type)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(EXECUTABLE_OUTPUT_PATH ../bin/)

################################## RType_server #####################################
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
	srcs/server/core/GameUtils.cpp
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

#server includes files
set(server_includes_directories
	srcs/server/core/
	srcs/server/core/missiles/
	srcs/server/core/monsters/
	srcs/server/misc/
	srcs/server/network/
	srcs/misc/
	srcs/misc/network/
	srcs/common/
	)

foreach(DIRECTORY ${server_includes_directories}) 
    # Get the directory of the source file
    FILE(GLOB tmp RELATIVE "${CMAKE_SOURCE_DIR}/" ${DIRECTORY}/*.hpp)
    set(server_includes ${server_includes} ${tmp})
endforeach()

if (UNIX)
set(server_sources ${server_sources} srcs/common/linux_specific/CULibLoader.cpp)
set(server_includes_directories ${server_includes_directories} srcs/common/linux_specific)
endif (UNIX)
if (WIN32)
set(server_sources ${server_sources} srcs/common/windows_specific/CWLibLoader.cpp)
set(server_includes_directories ${server_includes_directories} srcs/common/windows_specific)
endif (WIN32)

add_executable(RType_server ${server_sources} ${server_includes})

set_target_properties(RType_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set_target_properties(RType_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

target_compile_features(RType_server PRIVATE cxx_range_for)
target_include_directories(RType_server PRIVATE ${server_includes_directories})
if (UNIX)
target_link_libraries(RType_server -lpthread)
target_link_libraries(RType_server -ldl)
endif (UNIX)

#source_group(ServerIncludes FILES ${server_includes})
################################## !RType_server #####################################

################################## RType_client #####################################
#client sources files
set(client_sources 
	srcs/client/core/main.cpp 
	srcs/client/core/Menu.cpp
	srcs/client/core/Player.cpp 
	srcs/client/core/Game.cpp
	srcs/client/core/Client.cpp
	srcs/client/unit/AUnit.cpp
	srcs/client/unit/UnitFactory.cpp
	srcs/client/graphics/List.cpp
	srcs/client/graphics/Font.cpp
	srcs/client/graphics/Animation.cpp 
	srcs/client/graphics/ClickableBtn.cpp
	srcs/client/graphics/Editable.cpp
	srcs/client/graphics/Error.cpp
	srcs/client/graphics/GameListItem.cpp
	srcs/client/sound/SoundPlayer.cpp
	
	srcs/client/network/NetClient.cpp
	srcs/misc/network/Networker.cpp
	srcs/misc/network/UdpSocket.cpp
	srcs/misc/network/NetManager.cpp
	srcs/misc/APacket.cpp
	srcs/misc/ClientConnexionPacket.cpp
	srcs/misc/ClientGameConnectPacket.cpp
	srcs/misc/ClientGameInfoPacket.cpp
	srcs/misc/ClientKeyboardPressPacket.cpp
	srcs/misc/ServerConnexionPacket.cpp
	srcs/misc/ServerPlayerMovePacket.cpp
	srcs/misc/ServerGameConnectPacket.cpp
	srcs/misc/ServerTimerRefreshPacket.cpp
	srcs/misc/ServerGameInfoPacket.cpp
	srcs/misc/ServerUnitDiePacket.cpp
	srcs/misc/ServerPingPacket.cpp
	srcs/misc/ServerUnitSpawnPacket.cpp
	srcs/client/misc/Time.cpp 
	srcs/misc/Lock.cpp
	)

#client includes files
set(client_includes_directories
	srcs/client/core
	srcs/client/graphics
	srcs/client/sound
	srcs/client/network
	srcs/client/unit
	srcs/client/unit/MonsterTest
	srcs/client/unit/BasicMissile
	srcs/client/misc
	srcs/misc
	srcs/common
	srcs/misc/network
	)


foreach(DIRECTORY ${client_includes_directories}) 
    # Get the directory of the source file
    FILE(GLOB tmp RELATIVE "${CMAKE_SOURCE_DIR}/" ${DIRECTORY}/*.hpp)
    set(client_includes ${client_includes} ${tmp})
endforeach()

if (WIN32)
set(client_sources ${client_sources} srcs/common/windows_specific/CWLibLoader.cpp)
set(client_includes_directories ${client_includes_directories} srcs/common/windows_specific)
elseif (UNIX)
set(client_sources ${client_sources} srcs/common/linux_specific/CULibLoader.cpp)
set(client_includes_directories ${client_includes_directories} srcs/common/linux_specific)
endif()

add_executable(RType_client ${client_sources} ${client_includes})

set_target_properties(RType_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set_target_properties(RType_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

target_compile_features(RType_client PRIVATE cxx_range_for)
target_include_directories(RType_client PRIVATE ${client_includes_directories})
if (UNIX)
target_link_libraries(RType_client -lpthread)
target_link_libraries(RType_client -ldl)
endif (UNIX)

#source_group(ClientIncludes FILES ${client_includes})
################################## !RType_client #####################################

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

if (UNIX)
add_library(ServerMonsterTest SHARED
	srcs/common/linux_specific/CULibLoader.cpp
	srcs/server/core/monsters/MonsterTest.cpp
	srcs/server/core/AUnit.cpp
	srcs/server/core/AMissile.cpp
	srcs/server/core/MissileFactory.cpp
	srcs/server/core/AMonster.cpp
	srcs/server/core/GameUtils.cpp
	srcs/server/misc/Timer.cpp)
endif (UNIX)

if (WIN32)
add_library(ServerMonsterTest SHARED
	srcs/common/windows_specific/CWLibLoader.cpp
	srcs/server/core/monsters/MonsterTest.cpp
	srcs/server/core/AUnit.cpp
	srcs/server/core/AMissile.cpp
	srcs/server/core/MissileFactory.cpp
	srcs/server/core/AMonster.cpp
	srcs/server/core/GameUtils.cpp
	srcs/server/misc/Timer.cpp)
endif (WIN32)

target_include_directories(ServerMonsterTest PRIVATE ${server_includes_directories})
target_compile_features(ServerMonsterTest PRIVATE cxx_range_for)
if (UNIX)
set_target_properties(ServerMonsterTest PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../libs/server/)
set_target_properties(ServerMonsterTest PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ../libs/server/)
set_target_properties(ServerMonsterTest PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ../libs/server/)
endif(UNIX)
if (WIN32)
set_target_properties(ServerMonsterTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../libs/server/)
set_target_properties(ServerMonsterTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../libs/server/)
set_target_properties(ServerMonsterTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../libs/server/)
endif (WIN32)

add_library(ServerBasicMissile SHARED
	srcs/server/core/missiles/BasicMissile.cpp
	srcs/server/core/AUnit.cpp
	srcs/server/core/AMissile.cpp
	srcs/server/core/GameUtils.cpp
	srcs/server/misc/Timer.cpp
	)

target_include_directories(ServerBasicMissile PRIVATE ${server_includes_directories})
target_compile_features(ServerBasicMissile PRIVATE cxx_range_for)
if (UNIX)
set_target_properties(ServerBasicMissile PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../libs/server/)
set_target_properties(ServerBasicMissile PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ../libs/server/)
set_target_properties(ServerBasicMissile PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ../libs/server/)
endif(UNIX)
if (WIN32)
set_target_properties(ServerBasicMissile PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../libs/server/)
set_target_properties(ServerBasicMissile PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../libs/server/)
set_target_properties(ServerBasicMissile PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../libs/server/)
endif (WIN32)

add_library(ClientMonsterTest SHARED
	srcs/client/unit/MonsterTest/MonsterTest.cpp
	srcs/client/unit/AUnit.cpp
	srcs/client/graphics/Animation.cpp
	srcs/client/misc/Time.cpp
	)
target_include_directories(ClientMonsterTest PRIVATE ${client_includes_directories})
target_compile_features(ClientMonsterTest PRIVATE cxx_range_for)
if (UNIX)
set_target_properties(ClientMonsterTest PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../libs/client/)
set_target_properties(ClientMonsterTest PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ../libs/client/)
set_target_properties(ClientMonsterTest PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ../libs/client/)
endif(UNIX)
if (WIN32)
set_target_properties(ClientMonsterTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../libs/client/)
set_target_properties(ClientMonsterTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../libs/client/)
set_target_properties(ClientMonsterTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../libs/client/)
endif (WIN32)

add_library(ClientBasicMissile SHARED
	srcs/client/unit/MonsterTest/MonsterTest.cpp
	srcs/client/unit/AUnit.cpp
	srcs/client/graphics/Animation.cpp
	srcs/client/misc/Time.cpp
	)
target_include_directories(ClientBasicMissile PRIVATE ${client_includes_directories})
target_compile_features(ClientBasicMissile PRIVATE cxx_range_for)
if (UNIX)
set_target_properties(ClientBasicMissile PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../libs/client/)
set_target_properties(ClientBasicMissile PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ../libs/client/)
set_target_properties(ClientBasicMissile PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ../libs/client/)
endif(UNIX)
if (WIN32)
set_target_properties(ClientBasicMissile PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../libs/client/)
set_target_properties(ClientBasicMissile PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../libs/client/)
set_target_properties(ClientBasicMissile PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../libs/client/)
endif (WIN32)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})

# Detect and add SFML
if (WIN32)
	set(SFML_ROOT C:/libs/SFML-2.3.2)
endif()

find_package(SFML 2.1 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(RType_client ${SFML_LIBRARIES})
  target_link_libraries(ClientMonsterTest ${SFML_LIBRARIES})
  target_link_libraries(ClientBasicMissile ${SFML_LIBRARIES})
endif()

FILE(GLOB_RECURSE all_files *.*pp)

foreach(FILE ${all_files}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.hpp")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
