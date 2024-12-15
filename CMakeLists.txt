cmake_minimum_required(VERSION 3.1)

project (compiler)

set(SOURCE_EXE main.cpp)

include_directories(parser)
include_directories(lexer)
include_directories(syntaxer)

add_executable(main ${SOURCE_EXE})

add_subdirectory(parser)
add_subdirectory(lexer)
add_subdirectory(syntaxer)

target_link_libraries(main parser)
target_link_libraries(main lexer)
target_link_libraries(main syntaxer)
