cmake_minimum_required(VERSION 2.6)

project(R-Type)

set(EXECUTABLE_OUTPUT_PATH ../)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

#Etape1 sources files
set(etape1_sources
	main.cpp
)

add_executable(test_thread ${etape1_sources})
set_property(TARGET test_thread PROPERTY CXX_STANDARD 11)
