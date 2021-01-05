set(BINARY ${CMAKE_PROJECT_NAME}_examples)

file(GLOB_RECURSE EXAMPLES_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(${BINARY} ${EXAMPLES_SOURCES})

target_link_libraries(${BINARY} PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main gmock)

# compile this target as c++14
# this target only needs 14 but more importantly, compiling at least one target
# as 14 guarantees that the code works for this standard version 
set_target_properties(${BINARY} PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)