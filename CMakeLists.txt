cmake_minimum_required(VERSION 3.0)

PROJECT(mu)

set(CMAKE_CXX_STANDARD 14)

include_directories(mu)

add_subdirectory(mu)
add_subdirectory(tests)
add_subdirectory(dependencies/googletest)