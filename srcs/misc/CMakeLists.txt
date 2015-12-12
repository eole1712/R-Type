cmake_minimum_required(VERSION 3.1)

project(R-Type)

set(EXECUTABLE_OUTPUT_PATH ../)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

#Etape1 sources files
set(etape1_sources
	main.cpp
	Lock.cpp
)

add_executable(test_thread ${etape1_sources})
target_compile_features(test_thread PRIVATE cxx_range_for)
if (UNIX)
	target_link_libraries(test_thread -lpthread)
endif (UNIX)	
