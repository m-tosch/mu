cmake_minimum_required(VERSION 3.0)

PROJECT(mu)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -Werror -Wall" )

# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
# if(CMAKE_COMPILER_IS_GNUCXX) # change this if for custom build task later
#     include(CodeCoverage)
#     setup_target_for_coverage(mu_coverage mu_test coverage)
#     #target_link_libraries(${PROJECT_TEST_NAME} gcov)
#     SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
# endif()

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
# SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
# SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

include_directories(include/mu)

add_subdirectory(include)
add_subdirectory(tests)
add_subdirectory(dependencies/googletest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# NOTES COVERAGE REPORT GENERATION (GCOV & LCOV)
# 1. build w/cmake (generates .gcno files)
# 2. run mu/build/tests/mu_tests (generates .gcda files)
# 3. gcov main.cpp.gcno

# 4. lcov --directory . --capture --output-file main_coverage.info
# lcov --extract main_coverage.info "*\/mu\/*" --directory . --output-file main_coverage.info
# TBD: exclude gtest, c++ etc. and only include mu headers

# 5. genhtml main_coverage.info --output-directory out

# TODO
# extension using lcov*.info
# Code Coverage Highlighter
# brainfit.vscode-coverage-highlighter
