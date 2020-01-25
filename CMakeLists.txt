cmake_minimum_required(VERSION 3.5)

project(al C)

set(AL_MAJOR_VERSION 0)
set(AL_MINOR_VERSION 0)
set(AL_MICRO_VERSION 1)
set(AL_VERSION ${AL_MAJOR_VERSION}.${AL_MINOR_VERSION}.${AL_MICRO_VERSION})

# set default build type if not specified by user
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE   "-O2")
set(CMAKE_C_FLAGS_DEBUG     "-g -O0")

file(GLOB al_srcs src/*.c)

add_library(al ${al_srcs})

if(CMAKE_BUILD_TYPE STREQUAL "debug")
    option(ENABLE_TESTS "Build tests" ON)
    option(ENABLE_VALGRIND_TESTS "Build tests with valgrind" ON)
endif()

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(ENABLE_TESTS)
