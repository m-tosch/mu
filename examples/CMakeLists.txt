set(BINARY ${CMAKE_PROJECT_NAME}_examples)

file(GLOB_RECURSE EXAMPLES_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(${BINARY} ${EXAMPLES_SOURCES})

target_link_libraries(${BINARY} PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main gmock)

# add_dependencies(${CMAKE_PROJECT_NAME}_tests ${BINARY})
set(cmd "${CMAKE_CURRENT_BINARY_DIR}/${BINARY}")
add_test(NAME ${BINARY} COMMAND ${cmd} --gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR})
