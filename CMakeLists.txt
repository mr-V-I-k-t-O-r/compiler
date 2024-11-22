cmake_minimum_required(VERSION 3.1)

project (compiler)

set(SOURCE_EXE main.cpp)

include_directories(lexer)
include_directories(parser)

add_executable(main ${SOURCE_EXE})

add_subdirectory(lexer)
add_subdirectory(parser)

target_link_libraries(main lexer)
target_link_libraries(main parser)