#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper_functions.h"
#include "generate_list.h"

char *p_cust(Customer *cust, int socket)
{
	/*Prints All Fields In Customer*/
	char output[400];
	char *op = output;
	sprintf(output, "%s %s %s %s %d/%d/%d %d\n",
        cust->first_name, 
        cust->last_name,
        cust->id,
        cust->phone_number,
        cust->date.month,
        cust->date.day,
        cust->date.year,
        cust->debt);

	printf("%s", output);
	return op;
}

void output_error(char *str, int socket) 
{
	printf("%s\n", str);
}

int main(int argc, char **argv)
{
	if (argc < 2)
    {
        printf("Usage: %s <database>\n", argv[0]);
        return 1;
    }

	Customer *head = NULL;
	char buf[265];
	char *database = argv[1];
	FILE *ptr = fopen(database, "r");

	home_screen(ptr, &head, buf, NULL, p_cust, output_error);
	printf("\n<-");
	fgets(buf, 265, stdin);

	while (strcmp(buf, "quit\n") != 0)
	{
		program(ptr, head, buf, NULL, p_cust, output_error);
		printf("\n<-");
		fgets(buf, 265, stdin);
	}
	Free_All(&head);
	fclose(ptr);

	program(ptr, head, buf, NULL, p_cust, output_error);

	return 0;
}
