local: main.o helper_functions.o
	gcc -g main.o helper_functions.o -o local

main.o: main.c
	gcc -g -c main.c

helper_functions.o: helper_functions.c
	gcc -g -c helper_functions.c