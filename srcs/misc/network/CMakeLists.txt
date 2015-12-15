cmake_minimum_required(VERSION 3.1)

project(RType)

set(EXECUTABLE_OUTPUT_PATH ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
include_directories(../)
include_directories(./)
include_directories(../../server/network/)
include_directories(../../client/network/)

set(network_sources
  ../Lock.cpp
  ../APacket.cpp
  ../ClientConnexionPacket.cpp
  ../ServerConnexionPacket.cpp
  ../ClientGameConnectPacket.cpp
  ../ClientGameInfoPacket.cpp
  ../ServerGameConnectPacket.cpp
  ../ServerGameInfoPacket.cpp
  NetManager.cpp
  UdpSocket.cpp
  Networker.cpp
  )

set(server_sources
  ../../server/network/NetServer.cpp
  main_server.cpp
  )

set(client_sources
  ../../client/network/NetClient.cpp
  main_client.cpp
  )

add_executable(server ${network_sources} ${server_sources})
add_executable(client  ${client_sources} ${network_sources})
target_compile_features(server PRIVATE cxx_range_for)
target_compile_features(client PRIVATE cxx_range_for)
if (UNIX)
  target_link_libraries(server -lpthread)
  target_link_libraries(client -lpthread)
endif (UNIX)
