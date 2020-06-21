cmake_minimum_required(VERSION 3.0)

PROJECT(mu)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Debug")

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall --coverage")

include_directories(include/mu)

add_subdirectory(include)
add_subdirectory(tests)
add_subdirectory(dependencies/googletest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
