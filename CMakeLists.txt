cmake_minimum_required(VERSION 3.13)
project(assembler-HW)

SET(GCC_FLAGS_PEDANTIC "-Wall -ansi -pedantic")
SET(GCC_FLAGS "-ansi")
add_definitions("-Wall -ansi -pedantic")

add_executable(
        assembler-HW
        main.c
        structs/ParsedFile.c
        structs/LineOfCode.c
        structs/Token.c
        structs/BinaryCommand.c
        utils/string_utils.c
        assembler.c
        structs/SymbolTable.c
)