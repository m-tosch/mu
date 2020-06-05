set(BINARY ${CMAKE_PROJECT_NAME})

add_library(${BINARY}_lib INTERFACE)

target_include_directories(${BINARY}_lib INTERFACE .)