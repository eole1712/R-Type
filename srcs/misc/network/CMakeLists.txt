cmake_minimum_required(VERSION 2.6)

project(RType)

set(EXECUTABLE_OUTPUT_PATH ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

set(CMAKE_CXX_FLAGS "-std=c++11")

set(network_sources
  NetManager.cpp
  UdpSocket.cpp
  )

set(sender_sources
  main_send.cpp
  )

set(receiver_sources
  main_receive.cpp
  )

add_executable(sender ${network_sources} ${sender_sources})
add_executable(receiver  ${receiver_sources} ${network_sources})
if (UNIX)
  target_link_libraries(sender -lpthread)
  target_link_libraries(receiver -lpthread)
endif (UNIX)
