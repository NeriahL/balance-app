#include "program_functionality.h"

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

	else if(print_validation_msg(customer, NULL, socket, print_msg) == 1)
	{
		free(customer);
		customer = NULL;
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
	char op[3] = {0};
	char *param;
	char *str;
	char *val;
	char cleaned1[100] = {0};
	char cleaned2[100] = {0};
	char *cleaned_param = NULL;
	char *cleaned_val = NULL;
	FILE *ptr = fopen("database.csv", "r");

	Customer *customer = calloc(1, sizeof(Customer));

	strcpy(op, find_op(buf));

	param = strtok(buf, op);
	str = strtok(NULL, ",");

	while (str != NULL) //running through portions of query and populating Customer.
	{
		if (param !=NULL)
		{
			strcpy(cleaned1, clean(param));
			cleaned_param = cleaned1;
		}
		if (str != NULL)
		{
			strcpy(cleaned2, clean(str));
			cleaned_val = cleaned2;
		}
		populate_customer(head, cleaned_param, cleaned_val, customer, socket, print_msg);
		
		if (customer == NULL)
			break;	

		param = strtok(NULL, op);
		str = strtok(NULL, ",");
	}
	//write_to_database(ptr, customer); //write to Database
	//output_error("Added debt listing\n");
	int found = delete(ptr, &head, customer, socket, print_msg); //deletes node if current node is same customer.

	if(!found)
		insert(&head, customer);	//insert new node.
}

void handle_select(Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket))
{
	char op[3] = {0};
	char *param;
	char *str;
	char *val;
	char cleaned1[100] = {0};
	char cleaned2[100] = {0};
	char *cleaned_param = NULL;
	char *cleaned_val = NULL;

	strcpy(op, find_op(buf));
		
	if (strcmp(op, "!=")==0)
	{
		param = strtok(buf, "!");
		val = strtok(NULL, "=");
	}
	else
	{
		param = strtok(buf, op);
		val = strtok(NULL, op);
	}
	
	if (param !=NULL)
	{
		strcpy(cleaned1, clean(param));
		cleaned_param = cleaned1;
	}
	if (val != NULL)
	{
		strcpy(cleaned2, clean(val));
		cleaned_val = cleaned2;
	}
	
	Customer *temp_customer = calloc(1, sizeof(Customer));
	populate_customer(head, cleaned_param, cleaned_val, temp_customer, socket, print_msg);

	if (temp_customer == NULL)
		return;
	else if (strcmp(cleaned_param, "first name") == 0)
		print_search_results(head, temp_customer, op, compare_first_name, socket, print_cust);
	else if (strcmp(cleaned_param, "last name") == 0 || strcmp(cleaned_param, "second name") == 0)
		print_search_results(head, temp_customer, op, compare_last_name, socket, print_cust);
	else if (strcmp(cleaned_param, "id") == 0)
		print_search_results(head, temp_customer, op, compare_id, socket, print_cust);
	else if (strcmp(cleaned_param, "phone number") == 0 || strcmp(cleaned_param, "phone") == 0)
		print_search_results(head, temp_customer, op, compare_phone_number, socket, print_cust);
	else if (strcmp(cleaned_param, "date") == 0)
		print_search_results(head, temp_customer, op, compare_date, socket, print_cust);
	else if(strcmp(cleaned_param, "debt") == 0)
		print_search_results(head, temp_customer, op, compare_debt, socket, print_cust);
	
	free(temp_customer);
	temp_customer = NULL;
}

void list_init(FILE *ptr, Customer **head, char *buf, int socket, PRINT_CUST(cust, socket) ,PRINT_MSG(cust, socket))
{
	fgets(buf, 265, ptr);

	//Prints customers in database.
	while (fgets(buf, 265, ptr)) 
	{
		Customer *customer = calloc(1, sizeof(Customer));
		sscanf(buf, "%s , %s , %s , %s , %d/%d/%d , %d",
		customer->first_name,
		customer->last_name,
		customer->id,
		customer->phone_number,
		&customer->date.month,
		&customer->date.day,
		&customer->date.year,
		&customer->debt);

		int found = delete(ptr, head, customer, socket, print_msg);
		if (!found)
			insert(head, customer);
	}
	if (print_cust == NULL)
	{
		print_search_results(*head, NULL, "*", compare_debt, socket, print_cust);
	}
}

void handle_options(FILE *ptr, Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket))
{
	char *command;
	char op[3] = {0};
	char *buffer;
	
	command = strtok_r(buf, " ", &buffer);
	command = clean(command);
	
	if (strcmp(command, "set") == 0)
		handle_set(head, buffer, socket, print_msg);
	else if (strcmp(command, "select") == 0)
		handle_select(head, buffer, socket, print_cust, print_msg);
	else if (strcmp(command, "print") == 0)
		print_search_results(head, NULL, "*", compare_debt, socket, print_cust);
	else if (strcmp(command, "quit") == 0)
		return;
	else 
		print_msg("Could not identify command, please enter <set>, <select>, <print> or <quit>", socket);
		
}
