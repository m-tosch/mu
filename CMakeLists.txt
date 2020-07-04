cmake_minimum_required(VERSION 3.0)

PROJECT(mu)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS "-g -O0 -Wall")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/mu)

add_subdirectory(include)
add_subdirectory(tests)
add_subdirectory(dependencies/googletest)
