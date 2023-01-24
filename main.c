#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper_functions.h"

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

void Delete(Customer **head, Customer **customer)
{
	/*Function Removes Customer From Linked List
	
	head: &Customer.
	customer: &Customer.*/
	if (*head == NULL || *customer == NULL)
	{
		return;
	}
	
	Customer *run = (*head)->next;
	Customer *trail = *head;

	if (!strcmp((*head)->id, (*customer)->id)) //checks if ID already exists in the system
	{	
		if (validate_id(*customer, *head) == 1) //checks if names of customer and head are different.
		{
			free(*customer); //frees customer, as ID is in the system under different name
			*customer = NULL;
			return;
		}
		
		//Removes node

		Customer *temp = trail;
		(*customer)->debt += trail->debt;
		*head = trail->next;
		free(temp);
	}

	while (run != NULL)
	{
		if (!strcmp(run->id, (*customer)->id) == 1) //checks if ID already exists in the system
		{
			if (validate_id(*customer, run) == 1) //checks if names of customer and head are different.
			{
				free(*customer); //frees customer, as ID is in the system under different name
				*customer = NULL;
				return;
			}

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

void Print(Customer *head, Customer *pivot, char *comp, Customer *(comp_function)(Customer *customer, Customer *pivot))
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
				p_cust(run);
		} 
		else if (strcmp(comp, "*") == 0 || comp_function(run, pivot) == run) 
		{
			if (strcmp(comp, "!=") == 0 || strcmp(comp, "<") == 0 || strcmp(comp, "*") == 0) // print the following if node is unequal to or lesser than pivot value. Or print function was called in general.
				p_cust(run);
		}
		else 
		{
			if (strcmp(comp, "=") == 0 || strcmp(comp, "*") == 0) // print the following if node is equal to the pivot value. Or print function was called in general.
				p_cust(run);
		}
		run = run->next;
	}
}

void Run_Attributes(Customer *head, char *command, char *param, char *val, char *op, Customer **fill)
{
	/*Function Runs Through Attributes of Customer, Validated them, and Populates them and treates them according to the value of 'command'
	
	head: Customer. head of List.
	fill: &Customer. Customer to fill.
	command: char*. command entered in query.
	param: char*. parameter in query.
	val: char*. value entered in query.
	op: char*. operator entered in query.
	*/

	if (param == NULL)
	{
		printf("Error: Paramter has not been entered properly.\nPlease conform to the proper format:\n\t<parameter><operator><value>\n");
		return;
	}
	if (val == NULL)
	{
		printf("Error: Value has not been entered properly.\nPlease conform to the proper format:\t<parameter><operator><value>\n");
		return;
	}
	if (!strcmp(command, "set") && strcmp(op, "=")) // checks if 'set' command is paired with operator other than '='.
	{
		printf("Error: Operator can only be the equal operator < = >\n");
		free(*fill);
		*fill = NULL;
		return;
	}
	
	if (strcmp(param, "first name") == 0) // if param is first name, populate (*fill)->first_name.
	{
		strcpy((*fill)->first_name, val);
		
		if (strcmp(command, "select") == 0) // is 'command' is 'select', print values according to query.
		{
			Print(head, *fill, op, compare_first_name);
			printf("\n");
		}
	}
	else if (strcmp(param, "last name") == 0 || strcmp(param, "second name") == 0) // if param is last name or second name, populate (*fill)->last_name.
	{
		strcpy((*fill)->last_name, val);

		if (strcmp(command, "select") == 0)
		{
			Print(head, *fill, op, compare_last_name);
			printf("\n");
		}
	}
	else if (strcmp(param, "id") == 0) // if param is last name or second name, populate (*fill)->id.
	{
		strcpy((*fill)->id, val);
		if (strlen((*fill)->id) != 9 || atoi((*fill)->id) == 0) // validate ID as being 9 digits and numerical. if non-valid, free *fill.
		{
			printf("Customer %s %s has been entered with incorrect ID %s\n",
					(*fill)->first_name,
					(*fill)->last_name,
					(*fill)->id);
			free(*fill);
			*fill = NULL;
			return;
		}

		if (strcmp(command, "select") == 0)
		{
			Print(head, (*fill), op, compare_id);
			printf("\n");
		}
	}
	else if (strcmp(param, "phone number") == 0 || strcmp(param, "phone") == 0) // if param is phone number or phone, populate (*fill)->phone_number.
	{
		strcpy((*fill)->phone_number, val);
		if (strcmp(command, "select") == 0)
		{
			Print(head, (*fill), op, compare_phone_number);
			printf("\n");
		}
	}
	else if (strcmp(param, "date") == 0) // if param is date, populate (*fill)->date.
	{
		int day = 0;
		int month = 0;
		int year = 0;
		sscanf(val, "%d/%d/%d", &month, &day, &year);	
		(*fill)->date.day = day;
		(*fill)->date.month = month;
		(*fill)->date.year = year;

		if (((*fill)->date.day > 31 || (*fill)->date.day < 1) || 
					((*fill)->date.month > 12 || (*fill)->date.month <1) || 
					((*fill)->date.year > 2023))								// validate that date is legal, if non-valid, free *fill.
		{
			printf("Customer %s %s has been entered with incorrect date\n",
					(*fill)->first_name,
					(*fill)->last_name);
			free(*fill);
			*fill = NULL;
			return;
		}

		if (strcmp(command, "select") == 0)
		{
			Print(head, (*fill), op, compare_date);
			printf("\n");
		}
	}
	else if (strcmp(param, "debt") == 0) // if param is debt, populate (*fill)->debt.
	{
		(*fill)->debt = atoi(val);

		if (strcmp(command, "select") == 0)
		{
			Print(head, (*fill), op, compare_debt);
			printf("\n");
		}
	}
	else
	{
		printf("Error: %s is an unknow parameter. Please enter the parameters correctly and in their correct format so as to avoid errors.\n", param);
		free(*fill);
		*fill = NULL;
	}
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

Customer *generate_node(Customer **head, char *buf, char *command, FILE *ptr)
{
	/*Function Generates Node for search or additon.
	
	head: &Customer.
	buf: char*. query.
	command: char*.
	ptr: FILE *.

	op: char*. operator used in query.
	param: char*. parameter in query.
	str: char*. section of query.
	val: char*. value in query.
	cleaned1: char*. memory allocated to cleaning up parameter.
	cleaned2: char*. memory allocated to cleaning up parameter.
	cleaned_param: char*. pointer to cleaned param.
	cleaned_val: char*. pointer to cleaned val.
	*/
	Customer *customer = calloc(1, sizeof(Customer));

	char op[3] = {0};
	char *param;
	char *str;
	char *val;
	char cleaned1[100] = {0};
	char cleaned2[100] = {0};
	char *cleaned_param = NULL;
	char *cleaned_val = NULL;

	// find operator used in query and assigning it to 'op'
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

	// initial reading from Database
	if (command == NULL)
	{
		sscanf(buf, "%s , %s , %s , %s , %d/%d/%d , %d",
		customer->first_name,
		customer->last_name,
		customer->id,
		customer->phone_number,
		&customer->date.month,
		&customer->date.day,
		&customer->date.year,
		&customer->debt);
	}
	// execute option if command is 'set'.
	else if (strcmp(command, "set") == 0)
	{
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
			Run_Attributes(*head, command, cleaned_param, cleaned_val, op, &customer);
			
			if (customer == NULL)
				break;	

			param = strtok(NULL, op);
			str = strtok(NULL, ",");
		}
		write_to_database(ptr, customer); //write to Database
	}
	// execute option of command is 'select'. Parses, cleans str, and populates Customer.
	else if(strcmp(command, "select") == 0)
	{
		str = strtok(buf, "\n");
		
		if (strcmp(op, "!=")==0)
		{
			param = strtok(str, "!");
			val = strtok(NULL, "=");
		}
		else
		{
			param = strtok(str, op);
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
		
		Run_Attributes(*head, command, cleaned_param, cleaned_val, op, &customer);
		free(customer);
		customer = NULL;
	}

	Delete(head, &customer); //deletes node if current node is same customer.
	Insert(head, customer);	//insert new node.
	return customer;
}

int main()
{
	
	
	return 0;
}
