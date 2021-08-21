
assembler: data_structures_functions.o parsing_error_checking.o defined_data_structures.o \
 first_pass.o compile_commands.o assembler.o create_files.o second_pass.o helper_functions.o assembler.h
	gcc -g -Wall -ansi -pedantic data_structures_functions.o parsing_error_checking.o defined_data_structures.o \
	first_pass.o compile_commands.o assembler.o create_files.o second_pass.o helper_functions.o assembler.h -o assembler
data_structures_functions.o: data_structures_functions.c assembler.h
	gcc -c -Wall -ansi -pedantic data_structures_functions.c -o data_structures_functions.o
parsing_error_checking.o: parsing_error_checking.c assembler.h
	gcc -c -Wall -ansi -pedantic parsing_error_checking.c -o parsing_error_checking.o
defined_data_structures.o: defined_data_structures.c assembler.h
	gcc -c -Wall -ansi -pedantic defined_data_structures.c -o defined_data_structures.o
first_pass.o: first_pass.c assembler.h
	gcc -c -Wall -ansi -pedantic first_pass.c -o first_pass.o
compile_commands.o: compile_commands.c assembler.h
	gcc -c -Wall -ansi -pedantic compile_commands.c -o compile_commands.o
assembler.o: assembler.c assembler.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o
create_files.o: create_files.c assembler.h
	gcc -c -Wall -ansi -pedantic create_files.c -o create_files.o
second_pass.o: second_pass.c assembler.h
	gcc -c -Wall -ansi -pedantic second_pass.c -o second_pass.o
helper_functions.o: helper_functions.c assembler.h
	gcc -c -Wall -ansi -pedantic helper_functions.c -o helper_functions.o


# cleanup
clean:
	rm *.o