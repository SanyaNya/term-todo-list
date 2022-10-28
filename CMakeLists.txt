cmake_minimum_required(VERSION 3.20)

project(todo-list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
