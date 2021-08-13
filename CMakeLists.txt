cmake_minimum_required(VERSION 3.13)
project(assembler-HW)

SET(GCC_FLAGS "-Wall -ansi -pedantic")
add_definitions(${GCC_FLAGS})

add_executable(assembler-HW parsing.c structs/ParsedFile.c structs/LineOfCode.c structs/Token.c structs/BinaryCommand.c)