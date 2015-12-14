cmake_minimum_required(VERSION 2.6)
project(RType)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(rtype_VERSION_MAJOR 1)
set(rtype_VERSION_MINOR 0)

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "rtype")
include_directories(BEFORE ../common/core)
include_directories(BEFORE ../common/core/missiles)
include_directories(BEFORE ../common/misc)
include_directories(BEFORE ../misc)

# ../common/misc/linux_specific/CULibLoader.cpp

add_executable(${EXECUTABLE_NAME} main.cpp Menu.cpp Animation.cpp ClickableBtn.cpp Time.cpp Timer.cpp Player.cpp Game.cpp AUnit.cpp  ../misc/Lock.cpp)

if (WIN32)
   include_directories(BEFORE ../common/misc/windows_specific)
else()
   target_link_libraries(${EXECUTABLE_NAME} -lpthread)
   target_link_libraries(${EXECUTABLE_NAME} -ldl)
   include_directories(BEFORE ../common/misc/linux_specific)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})

# Detect and add SFML
find_package(SFML 2.1 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
