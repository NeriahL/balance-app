#include "generate_list.h"
#include "main.h"

char *find_op(char *buf)
{
	char op[3] = {0};
	char *oper;

	if (strstr(buf, "="))
	{
		op[0] = '=';
		op[1] = '\0';
	}
	else if (strstr(buf, "<"))
	{
		op[0] = '<';
		op[1] = '\0';
	}
	else if (strstr(buf, ">"))
	{
		op[0] = '>';
		op[1] = '\0';
	}
	else if (strstr(buf, "!="))
	{
		op[0] = '!';
		op[1] = '=';
	}
	oper = op;
	return oper;
}

void write_to_database(FILE *ptr, Customer *customer)
{
	/*Writes to Database
	
	ptr: FILE *.
	customer: Customer.*/
	fclose(ptr);
			
	ptr = fopen("database.csv", "a");

	if (customer != NULL)
	{
		fprintf(ptr, "\n%s , %s , %s , %s , %d/%d/%d , %d",
		customer->first_name,
		customer->last_name,
		customer->id,
		customer->phone_number,
		customer->date.month,
		customer->date.day,
		customer->date.year,
		customer->debt);
	}

	fclose(ptr);
	fopen("database.csv", "r");
}

void Insert(Customer **head, Customer *customer)
{
	/*Function Inserts Node Into Linked List
	
	head: &Customer.
	customer: Customer.*/
	if (customer == NULL)
	{
		return;
	}
	
	if (*head == NULL)
	{
		*head = customer;
		customer->next = NULL;
		return;
	}
	if (customer->debt < (*head)->debt)
	{
		Customer *temp = customer;
		customer->next = *head;
		*head = temp;
		return;
	}

	Customer *run = (*head)->next;
	Customer *trail = *head;

	while (run != NULL && customer->debt > run->debt)
	{
		run = run->next;
		trail = trail->next;
	}
	trail->next = customer;
	customer->next = run;
	return;
}

void Delete(FILE *ptr, Customer **head, Customer **customer, int socket, PRINT_MSG(str, socket))
{
	/*Function Removes Customer From Linked List
	
	head: &Customer.
	customer: &Customer.*/

	if (*head == NULL || *customer == NULL)
		return;
	
	Customer *run = (*head)->next;
	Customer *trail = *head;

	if (strcmp((*head)->id, (*customer)->id) == 0) //checks if ID already exists in the system
	{	
		puts((*head)->id);
		if (validate_id(*customer, *head, socket, print_msg) == 1) //checks if names of customer and head are different.
		{
			
			free(*customer); //frees customer, as ID is in the system under different name
			*customer = NULL;
			return;
		}
		if (compare_date(*head, *customer) == *head)
		{
			(*customer)->date.day = (*head)->date.day;
			(*customer)->date.month = (*head)->date.month;
			(*customer)->date.year = (*head)->date.year;
		}
		
		//Removes node

		Customer *temp = trail;
		(*customer)->debt += trail->debt;
		*head = trail->next;
		free(temp);
	}

	while (run != NULL)
	{
		if (strcmp(run->id, (*customer)->id) == 0) //checks if ID already exists in the system
		{
			if (validate_id(*customer, run, socket, print_msg) == 1) //checks if names of customer and head are different.
			{
				free(*customer); //frees customer, as ID is in the system under different name
				*customer = NULL;
				return;
			}
			if (compare_date(run, *customer) == run)
			{
				(*customer)->date.day = run->date.day;
				(*customer)->date.month = run->date.month;
				(*customer)->date.year = run->date.year;
			}

			if (socket > 0)
				write_to_database(ptr, *customer);
			

			//Removes node
			
			Customer *temp = run;
			(*customer)->debt += run->debt;
			trail->next = run->next;
			free(temp);
		}
		trail = trail->next;
		run = run->next;
	}
}

void Screen(Customer *head, Customer *pivot, char *comp, COMPARE(customer, pivot), int socket, PRINT_CUST(cust, socket))
{
	/*Function Prints List in accordance with Query
	
	head: Customer. Head of List.
	pivot: Customer. struct bearing information from query.
	comp: char*. operator from query.
	comp_function: Customer. comparison function needed in order to judge if node conforms to query.
	*/
	if (head == NULL)
	{
		return;
	}

	Customer *run = head;

	while (run != NULL) //runs through Linked List
	{
		if (strcmp(comp, "*") == 0 || comp_function(pivot, run) == pivot)
		{
			if (strcmp(comp, "!=") == 0 || strcmp(comp, ">") == 0 || strcmp(comp, "*") == 0) // print the following if node is unequal to or greater than pivot value. Or print function was called in general.
				print_cust(run, socket);
		} 
		else if (strcmp(comp, "*") == 0 || comp_function(run, pivot) == run) 
		{
			if (strcmp(comp, "!=") == 0 || strcmp(comp, "<") == 0 || strcmp(comp, "*") == 0) // print the following if node is unequal to or lesser than pivot value. Or print function was called in general.
				print_cust(run, socket);
		}
		else 
		{
			if (strcmp(comp, "=") == 0 || strcmp(comp, "*") == 0) // print the following if node is equal to the pivot value. Or print function was called in general.
				print_cust(run, socket);
		}
		run = run->next;
	}
}

void Free_All(Customer **head)
{
	/*Function Frees Entire List*/

	Customer *run = NULL;
	
	while (run != NULL)
	{
		run = *head;
		*head = (*head)->next;
		free(run);
	}
}

void Fill_Attributes(Customer *head, char *param, char *val, Customer **fill, int socket, PRINT_MSG(str, socket))
{
	/*Function Runs Through Attributes of Customer, Validated them, Populates them and treates them according to the value of 'command'
	
	head: Customer. head of List.
	fill: &Customer. Customer to fill.
	command: char*. command entered in query.
	param: char*. parameter in query.
	val: char*. value entered in query.
	op: char*. operator entered in query.
	*/

    char out[400];

	val = lowercase(val);
	val[0] = toupper(val[0]);

	if (strcmp(param, "first name") == 0) // if param is first name, populate (*fill)->first_name.
		strcpy((*fill)->first_name, val);
		
	else if (strcmp(param, "last name") == 0 || strcmp(param, "second name") == 0) // if param is last name or second name, populate (*fill)->last_name.
		strcpy((*fill)->last_name, val);

	else if (strcmp(param, "id") == 0) // if param is last name or second name, populate (*fill)->id.
	{
		strcpy((*fill)->id, val);
		if (id_length(*fill, socket, print_msg) == 0)
		{
			free(*fill);
			*fill = NULL;
		}	
	}
	else if (strcmp(param, "phone number") == 0 || strcmp(param, "phone") == 0) // if param is phone number or phone, populate (*fill)->phone_number.
		strcpy((*fill)->phone_number, val);

	else if (strcmp(param, "date") == 0) // if param is date, populate (*fill)->date.
	{
		sscanf(val, "%d/%d/%d", &((*fill)->date.month), &((*fill)->date.day), &((*fill)->date.year));	
		if (validate_date(*fill, socket, print_msg) == 0)
		{
			free(*fill);
			*fill = NULL;
		}
		
	}
	else if (strcmp(param, "debt") == 0) // if param is debt, populate (*fill)->debt.
		(*fill)->debt = atoi(val);
	else
	{
        sprintf(out, "Error: %s is an unknow parameter. Please enter the parameters correctly and in their correct format so as to avoid errors.\n", param);
        PRINT_MSG(out, socket);
		free(*fill);
		*fill = NULL;
	}
}

void set(Customer *head, char *buf, int socket, PRINT_MSG(str, socket))
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

	Customer *fill = calloc(1, sizeof(Customer));

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
		Fill_Attributes(head, cleaned_param, cleaned_val, &fill, socket, print_msg);
		
		if (fill == NULL)
			break;	

		param = strtok(NULL, op);
		str = strtok(NULL, ",");
	}
	//write_to_database(ptr, fill); //write to Database
	//output_error("Added debt listing\n");
	Delete(ptr, &head, &fill, socket, print_msg); //deletes node if current node is same customer.
	Insert(&head, fill);	//insert new node.
	
}

void search(Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket))
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
	
	Customer *fill = calloc(1, sizeof(Customer));
	Fill_Attributes(head, cleaned_param, cleaned_val, &fill, socket, print_msg);

	if (fill == NULL)
		return;
	else if (fill->first_name[0] != '\0')
		Screen(head, fill, op, compare_first_name, socket, print_cust);
	else if (fill->last_name[0] != '\0')
		Screen(head, fill, op, compare_last_name, socket, print_cust);
	else if (fill->id[0] != '\0')
		Screen(head, fill, op, compare_id, socket, print_cust);
	else if (fill->phone_number[0] != '\0')
		Screen(head, fill, op, compare_phone_number, socket, print_cust);
	else if (fill->date.year > 0)
		Screen(head, fill, op, compare_date, socket, print_cust);
	else 
		Screen(head, fill, op, compare_debt, socket, print_cust);
	
	free(fill);
	fill = NULL;
}

void home_screen(FILE *ptr, Customer **head, char *buf, int socket, PRINT_CUST(cust, socket) ,PRINT_MSG(cust, socket))
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

		Delete(ptr, head, &customer, socket, print_msg);
		Insert(head, customer);
	}
	if (print_cust == NULL)
	{
		Screen(*head, NULL, "*", compare_debt, socket, print_cust);
	}
}

void program(FILE *ptr, Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket))
{
	char *command;
	char op[3] = {0};
	char *buffer;
	
	command = strtok_r(buf, " ", &buffer);
	command = clean(command);
	
	if (strcmp(command, "set") == 0)
		set(head, buffer, socket, print_msg);
	else if (strcmp(command, "select") == 0)
		search(head, buffer, socket, print_cust, print_msg);
	else if (strcmp(command, "print") == 0)
		Screen(head, NULL, "*", compare_debt, socket, print_cust);
	else if (strcmp(command, "quit") == 0)
		return;
	else 
		print_msg("Could not identify command, please enter <set>, <select>, <print> or <quit>", socket);
		
}
