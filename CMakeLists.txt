cmake_minimum_required(VERSION 3.0)

PROJECT(mu)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS "-g -Wall -fno-inline -fno-inline-small-functions -fno-default-inline --coverage")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/mu)

add_subdirectory(include)
add_subdirectory(tests)
add_subdirectory(dependencies/googletest)
