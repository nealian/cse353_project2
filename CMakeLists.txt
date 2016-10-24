cmake_minimum_required(VERSION 2.8)

project(project1)

include_directories(./)

set (CMAKE_CXX_COMPILER "/usr/bin/clang++")

set (DEBUG_FLAGS "-g -O0 -Wall -std=c++11 -stdlib=libc++ -pthread")
set (RELEASE_FLAGS  "-O3 -Wall -std=c++11 -stdlib=libc++ -pthread")

set (CMAKE_CXX_FLAGS_DEBUG  ${DEBUG_FLAGS})
set (CMAKE_CXX_FLAGS_RELEASE ${RELEASE_FLAGS})

set (CMAKE_CONFIGURATION_TYPES Debug Release)
set (CMAKE_BUILD_TYPE                "Debug")

file (GLOB_RECURSE NODE_SRC RELATIVE_PATH
  node/*.cpp
  node/*.hpp)
source_group ("node" FILES ${NODE_SRC})

file (GLOB_RECURSE SOCKET_SRC RELATIVE_PATH
        donahoo/*.cpp
        donahoo/*.hpp)
source_group ("socket" FILES ${SOCKETSRC})

set (COMPILER_SRC main.cpp
                    ${NODE_SRC}
                    ${SOCKET_SRC})

add_executable(project1 ${COMPILER_SRC})

set_property(TARGET project1 PROPERTY FOLDER "project1")
