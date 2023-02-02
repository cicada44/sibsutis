set(target_name computer)

set(CMAKE_C_COMPILER gcc)

add_library(
    ${target_name}
    STATIC
        libcomputer/comp.c
        libcomputer/comp.h
)

add_compile_options(-Wall -Werror -Wextra -pedantic)

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)