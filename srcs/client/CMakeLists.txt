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

add_executable(${EXECUTABLE_NAME} test.cpp Animation.cpp Time.cpp Player.cpp Game.cpp ../common/core/ABonus.cpp ../common/core/AMonster.cpp ../common/core/AUnit.cpp ../common/core/MonsterFactory.cpp ../common/core/AMissile.cpp ../common/misc/Timer.cpp ../common/misc/linux_specific/CULibLoader.cpp ../common/core/AObstacle.cpp ../common/core/MissileFactory.cpp ../common/core/missiles/BasicMissile.cpp)

if (WIN32)
   include_directories(BEFORE ../common/misc/windows_specific)
else()
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
