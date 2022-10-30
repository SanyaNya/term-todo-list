cmake_minimum_required(VERSION 3.20)

project(todo-list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_compile_options(
    -Wall
    -Wextra
    -Wconversion
    -Wsign-conversion
    $<$<CONFIG:DEBUG>:-O0>
    $<$<CONFIG:DEBUG>:-g3>
    $<$<CONFIG:DEBUG>:-fsanitize=address>
    $<$<CONFIG:DEBUG>:-fsanitize=undefined>
    $<$<CONFIG:RELEASE>:-O3>)

add_link_options(
    $<$<CONFIG:DEBUG>:-fsanitize=address>
    $<$<CONFIG:DEBUG>:-fsanitize=undefined>)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
