remote: generate_list.o server.o helper_functions.o
	gcc -g generate_list.o server.o helper_functions.o -o remote

server.o: server.c
	gcc -g -c server.c

generate_list.o: generate_list.c
	gcc -g -c generate_list.c

helper_functions.o: helper_functions.c
	gcc -g -c helper_functions.c


