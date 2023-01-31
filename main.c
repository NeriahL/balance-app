#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper_functions.h"
#include "generate_list.h"

void output_error(char *str)
{
	printf("%s", str);
}

char *p_cust(Customer *cust)
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

int main()
{
	FILE *ptr = fopen("database.csv", "r");
	Customer *head = NULL;
	char *command;
	char *str;
	char *val;
	char buf[265];

	fgets(buf, 265, ptr);

	//Prints customers in database.
	while (fgets(buf, 265, ptr)) 
	{
		generate_node(&head, buf, NULL, ptr);
	}
	Print(head, NULL, "*", compare_debt);
	
	//runs program until 'quit' is entered
	printf("\n<-");
	fgets(buf, 265, stdin);
	
	while (strcmp(buf, "quit\n") != 0)
	{
		command = strtok_r(buf, " ", &val);

		if (strcmp(command, "set") == 0 || strcmp(command, "select") == 0)
		{
			generate_node(&head, val, command, ptr);
		}
		else if (strcmp(command, "print\n") == 0)
		{
			Print(head, NULL, "*", compare_id);
		}
		else if (strcmp(command, "quit\n") == 0)
		{
			break;
		}
		else
		{
			printf("Error: Unknown command, please enter <set>, <select>, <print> or <quit> in their proper format.");
		}
		
		printf("\n<-");
		fgets(buf, 265, stdin);
	}
	
	Free_All(&head);

	fclose(ptr);
	
	return 0;
}
