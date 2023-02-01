set(target_name comp)

add_library(
    ${target_name}
    complib/comp.cpp
    complib/comp.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)