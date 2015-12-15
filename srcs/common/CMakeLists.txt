cmake_minimum_required(VERSION 3.1)

project(R-Type)

set(EXECUTABLE_OUTPUT_PATH ../../)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

#Etape1 sources files
if (UNIX)
set(etape1_sources
	main.cpp
	linux_specific/CULibLoader.cpp)
include_directories(./
  linux_specific/)
endif (UNIX)
if (WIN32)
set(etape1_sources
	main.cpp
	windows_specific/CWLibLoader.cpp)
include_directories(./
  windows_specific/)
endif (WIN32)

add_executable(test_libloader ${etape1_sources})
target_compile_features(test_libloader PRIVATE cxx_range_for)
if (UNIX)
	target_link_libraries(test_libloader -ldl)
endif (UNIX)	
