cmake_minimum_required(VERSION 3.1)

project(CPP_Hive)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O3 -flto -msse3 -mpopcnt -fwhole-program -march=native")

find_package(Boost COMPONENTS system thread program_options)

file(STRINGS "includelist.cmake" includes)

include_directories(${includes})
include(sourcelist.cmake)

find_library(pugiXML pugi)

add_executable(CPP_Hive_Client ${sources})

target_link_libraries(CPP_Hive_Client ${Boost_LIBRARIES})
target_link_libraries(CPP_Hive_Client "${pugi}")