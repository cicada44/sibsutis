set(target_name app)

set(CMAKE_C_COMPILER gcc)

add_executable(${target_name})

add_compile_options(-Wall -Wextra -Werror -pedantic)

target_sources(
    ${target_name}
    PRIVATE
        app/main.c
)

target_link_libraries(
    ${target_name}
    PRIVATE
        computer
)
