cmake_minimum_required(VERSION 2.6)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${HelloCMake_SOURCE_DIR}..)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Set version information in a config.h file
set(rtype_VERSION_MAJOR 1)
set(rtype_VERSION_MINOR 0)

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "rtype")
add_executable(${EXECUTABLE_NAME} test.cpp Animation.cpp Time.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})

# Detect and add SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
