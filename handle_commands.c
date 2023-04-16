#include "handle_commands.h"

int (*select_compare_function(char * parameter))(Customer *, char *)
{
	if (parameter == NULL)
		return NULL;
	
	if (!strcmp(parameter, "first name"))
		return &compare_first_name;

	else if (!strcmp(parameter, "last name") || !strcmp(parameter, "second name"))
		return &compare_last_name;

	else if (!strcmp(parameter, "id"))
		return &compare_id;

	else if (!strcmp(parameter, "phone number") || !strcmp(parameter, "phone"))
		return &compare_phone_number;

	else if (!strcmp(parameter, "date"))
		return &compare_date;

	else if(!strcmp(parameter, "debt"))
		return &compare_debt;
	else
		return NULL;
}

int populate_customer(Customer *head, char *param, char *val, Customer *customer)
{
	/*Function Runs Through Attributes of Customer, Validated them, Populates them and treates them according to the value of 'command'
	
	head: Customer. head of List.
	customer: &Customer. Customer to fill.
	command: char*. command entered in query.
	param: char*. parameter in query.
	val: char*. value entered in query.
	op: char*. operator entered in query.
	*/

	if (val == NULL || param == NULL)
		return 1;

    char out[400];

	val = lowercase(val);
	val[0] = toupper(val[0]);

	if (!strcmp(param, "first name")) // if param is 'first name', populate customer->first_name.
		strcpy(customer->first_name, val);
		
	else if (!strcmp(param, "last name") || !strcmp(param, "second name")) // if param is 'last name' or 'second name', populate customer->last_name.
		strcpy(customer->last_name, val);
	
	else if (!strcmp(param, "phone number") || !strcmp(param, "phone")) // if param is 'phone number' or 'phone', populate customer->phone_number.
		strcpy(customer->phone_number, val);
	
	else if (!strcmp(param, "debt")) // if param is 'debt', populate customer->debt.
		customer->debt = atoi(val);

	else if (!strcmp(param, "id")) // if param is 'id', populate customer->id.
		strcpy(customer->id, val);

	else if (!strcmp(param, "date")) // if param is 'date', populate customer->date.
		sscanf(val, "%d/%d/%d", &(customer->date.month), &(customer->date.day), &(customer->date.year));	

	else if(print_validation_msg(customer, NULL))
		return 1;

	else
	{
        sprintf(out, "Error: %s is an unknow parameter. Please enter the parameters correctly and in their correct format so as to avoid errors.", param);
		collect_errors(out);
		return 1;
	}

	return 0;
}

void handle_set(Customer *head, char *buf, int socket, PRINT_MSG(str, socket))
{
	FILE *ptr = fopen("database.csv", "r");
	Customer *customer = calloc(1, sizeof(Customer));
	char *str = strsep(&buf, ",");
	int err = 0;

	while (str != NULL) //running through portions of query and populating Customer.
	{
		char temp[100];
		strcpy(temp, str);
		char **query = parse_query_text(temp, socket, SET);
		err = populate_customer(head, query[0], query[2], customer);

		str = strsep(&buf, ",");
	}

	if (err == 1)
		customer = NULL;

	int found = delete(ptr, &head, customer, socket); //deletes node if current node is same customer.

	print_errors(print_msg, socket);

	if(!found)
		insert(&head, customer);	//insert new node.

	fclose(ptr);
}

void handle_select(Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(cust, socket))
{	
	char **query = parse_query_text(buf, socket, SELECT);

	print_errors(print_msg, socket);

	if(select_compare_function(query[0]) == NULL)
		return;

	int (*func_ptr)(Customer *, char *) = select_compare_function(query[0]);

	print_search_results(head, query[2], query[1], func_ptr, socket, print_cust);

	free(query);
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

// 6. test and make sure everything works. if not, compile a list of errors to straighten out.
// 7. get moving on tree data structure for database:
// 		a. write functions to create AVL trees for each attribute of Customer.
//		b. integrate functions with current function eco system (maybe using function pointers or 'same name' technique).
// 8. make program as modular as possible.