remote: string_methods.o generate_list.o server.o helper_functions.o validations.o program_functionality.o
	gcc -g string_methods.o generate_list.o server.o helper_functions.o validations.o program_functionality.o -o remote

local: string_methods.o generate_list.o main.o helper_functions.o validations.o program_functionality.o
	gcc -g string_methods.o generate_list.o main.o helper_functions.o validations.o program_functionality.o -o local

server.o: server.c
	gcc -g -c server.c

string_methods.o: string_methods.c
	gcc -g -o string_methods.c

generate_list.o: generate_list.c
	gcc -g -c generate_list.c

helper_functions.o: helper_functions.c
	gcc -g -c helper_functions.c

validations.o: validations.c
	gcc -g -c validations.c

program_functionality.o: program_functionality.c
	gcc -g -c program_functionality.c