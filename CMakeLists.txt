cmake_minimum_required(VERSION 3.15)
project(baltech_debian_tools C)

set(BALTECH_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BALTECH_OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BALTECH_OUTPUT_DIR}")

add_subdirectory(brp_lib)
add_subdirectory(bindings/c)
add_subdirectory(tools)