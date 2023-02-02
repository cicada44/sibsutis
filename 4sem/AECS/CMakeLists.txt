cmake_minimum_required(VERSION 3.22)

project(
    SimpleComputer
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
