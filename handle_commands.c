#include "handle_commands.h"

void populate_customer(Customer *head, char *param, char *val, Customer *customer, int socket, PRINT_MSG(str, socket))
{
	/*Function Runs Through Attributes of Customer, Validated them, Populates them and treates them according to the value of 'command'
	
	head: Customer. head of List.
	customer: &Customer. Customer to fill.
	command: char*. command entered in query.
	param: char*. parameter in query.
	val: char*. value entered in query.
	op: char*. operator entered in query.
	*/

    char out[400];

	val = lowercase(val);
	val[0] = toupper(val[0]);

	if (strcmp(param, "first name") == 0) // if param is 'first name', populate customer->first_name.
		strcpy(customer->first_name, val);
		
	else if (strcmp(param, "last name") == 0 || strcmp(param, "second name") == 0) // if param is 'last name' or 'second name', populate customer->last_name.
		strcpy(customer->last_name, val);
	
	else if (strcmp(param, "phone number") == 0 || strcmp(param, "phone") == 0) // if param is 'phone number' or 'phone', populate customer->phone_number.
		strcpy(customer->phone_number, val);
	
	else if (strcmp(param, "debt") == 0) // if param is 'debt', populate customer->debt.
		customer->debt = atoi(val);

	else if (strcmp(param, "id") == 0) // if param is 'id', populate customer->id.
		strcpy(customer->id, val);

	else if (strcmp(param, "date") == 0) // if param is 'date', populate customer->date.
		sscanf(val, "%d/%d/%d", &(customer->date.month), &(customer->date.day), &(customer->date.year));	

	else if(print_validation_msg(customer, NULL, socket, print_msg))
	{
		free(customer);
		customer = NULL;
		return;
	}
	else
	{
        sprintf(out, "Error: %s is an unknow parameter. Please enter the parameters correctly and in their correct format so as to avoid errors.\n", param);
        print_msg(out, socket);
		free(customer);
		customer = NULL;
	}

}

void handle_set(Customer *head, char *buf, int socket, PRINT_MSG(str, socket))
{
	FILE *ptr = fopen("database.csv", "r");
	Customer *customer = calloc(1, sizeof(Customer));
	char *str = strsep(&buf, ",");

	while (str != NULL) //running through portions of query and populating Customer.
	{
		char temp[100];
		strcpy(temp, str);
		char **query = parse_query_text(temp);
		populate_customer(head, query[0], query[2], customer, socket, print_msg);
		
		if (customer == NULL)
			break;

		str = strsep(&buf, ",");
	}

	int found = delete(ptr, &head, customer, socket, print_msg); //deletes node if current node is same customer.

	if(!found)
		insert(&head, customer);	//insert new node.
}

void handle_select(Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket))
{

	char ** query = parse_query_text(buf);
	
	Customer *temp_customer = calloc(1, sizeof(Customer));
	populate_customer(head, query[0], query[2], temp_customer, socket, print_msg);

	if (temp_customer == NULL)
		return;

	else if (!strcmp(query[0], "first name"))
		print_search_results(head, temp_customer, query[1], compare_first_name, socket, print_cust);

	else if (!strcmp(query[0], "last name") || !strcmp(query[0], "second name"))
		print_search_results(head, temp_customer, query[1], compare_last_name, socket, print_cust);

	else if (!strcmp(query[0], "id"))
		print_search_results(head, temp_customer, query[1], compare_id, socket, print_cust);

	else if (!strcmp(query[0], "phone number") || !strcmp(query[0], "phone"))
		print_search_results(head, temp_customer, query[1], compare_phone_number, socket, print_cust);

	else if (!strcmp(query[0], "date"))
		print_search_results(head, temp_customer, query[1], compare_date, socket, print_cust);

	else if(!strcmp(query[0], "debt"))
		print_search_results(head, temp_customer, query[1], compare_debt, socket, print_cust);
	
	free(query);
	free(temp_customer);
	temp_customer = NULL;
}

void handle_options(FILE *ptr, Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket))
{
	char *command;
	char *buffer;
	
	command = strtok_r(buf, " ", &buffer);
	command = clean(command);
	
	if (!strcmp(command, "set"))
		handle_set(head, buffer, socket, print_msg);
	else if (!strcmp(command, "select"))
		handle_select(head, buffer, socket, print_cust, print_msg);
	else if (!strcmp(command, "print"))
		print_search_results(head, NULL, "*", compare_debt, socket, print_cust);
	else if (!strcmp(command, "quit"))
		return;
	else 
		print_msg("Could not identify command, please enter <set>, <select>, <print> or <quit>", socket);
		
}


// 3. look into populate_customer returning a pointer to a function in addition to populating Customer Object or any other way to cut down on if/else mess.
// 6. test and make sure everything works. if not, compile a list of errors to straighten out.
// 7. get moving on tree data structure for database:
// 		a. write functions to create AVL trees for each attribute of Customer.
//		b. integrate functions with current function eco system (maybe using function pointers or 'same name' technique).
// 8. make program as modular as possible.
// 9. think about how to best change comparison functions and change them accordingly.