local: generate_list.o helper_functions.o main.o
	gcc -g generate_list.o helper_functions.o main.o -o local

main.o: main.c
	gcc -g -c main.c

generate_list.o: generate_list.c
	gcc -g -c generate_list.c

helper_functions.o: helper_functions.c
	gcc -g -c helper_functions.c


