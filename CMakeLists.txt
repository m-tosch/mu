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

# generate "compile_commands.json"
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set to "include" folder, so that header includes must be "mu/*.h"
include_directories(include)

# provide the header files as a library
add_library(${CMAKE_PROJECT_NAME}_lib INTERFACE)
target_include_directories(${CMAKE_PROJECT_NAME}_lib INTERFACE include/${CMAKE_PROJECT_NAME})

# subdirectories that have their own CMakeLists.txt
add_subdirectory(tests)
add_subdirectory(dependencies/googletest)
