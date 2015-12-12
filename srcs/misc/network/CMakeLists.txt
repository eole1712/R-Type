cmake_minimum_required(VERSION 3.1)

project(RType)

set(EXECUTABLE_OUTPUT_PATH ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
include_directories(../)

set(network_sources
  ../Lock.cpp
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
target_compile_features(sender PRIVATE cxx_range_for)
target_compile_features(receiver PRIVATE cxx_range_for)
if (UNIX)
  target_link_libraries(sender -lpthread)
  target_link_libraries(receiver -lpthread)
endif (UNIX)
