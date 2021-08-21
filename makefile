
assembler: BinaryCommand.o LineOfCode.o ParsedFile.o SymbolTable.o Token.o assembler.o main.o
	gcc -g -Wall -ansi -pedanticBinaryCommand.o LineOfCode.o ParsedFile.o SymbolTable.o Token.o assembler.o main.o -o assembler
BinaryCommand.o: BinaryCommand.c BinaryCommand.h
	gcc -c -Wall -ansi -pedantic BinaryCommand.c -o BinaryCommand.o
LineOfCode.o: LineOfCode.c LineOfCode.h
	gcc -c -Wall -ansi -pedantic LineOfCode.c -o LineOfCode.o
ParsedFile.o: ParsedFile.c ParsedFile.h
	gcc -c -Wall -ansi -pedantic ParsedFile.c -o ParsedFile.o
SymbolTable.o: SymbolTable.c SymbolTable.h
	gcc -c -Wall -ansi -pedantic SymbolTable.c -o SymbolTable.o
Token.o: Token.c Token.h
	gcc -c -Wall -ansi -pedantic Token.c -o Token.o
assembler.o: assembler.c assembler.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o
main.o: main.c main.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o


# cleanup
clean:
	rm *.o