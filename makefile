
assembler: BinaryCommand.o LineOfCode.o ParsedFile.o SymbolTable.o Token.o string_utils.o assembler.o main.o
	gcc -g -Wall -ansi -pedantic BinaryCommand.o LineOfCode.o ParsedFile.o SymbolTable.o Token.o string_utils.o assembler.o main.o -o assembler
BinaryCommand.o: structs/BinaryCommand.c structs/BinaryCommand.h
	gcc -c -Wall -ansi -pedantic structs/BinaryCommand.c -o BinaryCommand.o
LineOfCode.o: structs/LineOfCode.c structs/LineOfCode.h
	gcc -c -Wall -ansi -pedantic structs/LineOfCode.c -o LineOfCode.o
ParsedFile.o: structs/ParsedFile.c structs/ParsedFile.h
	gcc -c -Wall -ansi -pedantic structs/ParsedFile.c -o ParsedFile.o
SymbolTable.o: structs/SymbolTable.c structs/SymbolTable.h
	gcc -c -Wall -ansi -pedantic structs/SymbolTable.c -o SymbolTable.o
Token.o: structs/Token.c structs/Token.h
	gcc -c -Wall -ansi -pedantic structs/Token.c -o Token.o
utils/string_utils.o: utils/string_utils.c utils/string_utils.h
	gcc -c -Wall -ansi -pedantic utils/string_utils.c -o string_utils.o
assembler.o: assembler.c assembler.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o
main.o: main.c
	gcc -c -Wall -ansi -pedantic main.c -o main.o


# cleanup
clean:
	rm *.o