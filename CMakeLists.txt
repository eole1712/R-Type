cmake_minimum_required(VERSION 2.6)

project(RType)

set(EXECUTABLE_OUTPUT_PATH bin/$(CMAKE_BUILD_TYPE))

#All include directories
include_directories(
	includes/server
	includes/client
)

#Server sources files
set(server_sources
	srcs/server/main.cpp
#	srcs/server/core/server.cpp
)

add_executable(RType_server ${server_sources})

#Client sources files
set(client_sources
	srcs/client/main.cpp
	srcs/client/client.cpp
)
#add_executable(RType_client client_sources)
