set(BINARY ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME}_lib gtest_main gmock)

# compile only this target as c++17
set_target_properties(${BINARY} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)