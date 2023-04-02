#include "generate_list.h"
#include "main.h"

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

void insert(Customer **head, Customer *customer)
{
	/*Function inserts Node Into Linked List
	
	head: &Customer.
	customer: Customer.*/
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

int delete(FILE *ptr, Customer **head, Customer *customer, int socket, PRINT_MSG(str, socket))
{
	/*Function Removes Customer From Linked List
	
	head: &Customer.
	customer: &Customer.*/

	if (*head == NULL || customer == NULL)
		return 0;
	
	Customer *run = (*head)->next;
	Customer *trail = *head;

	if (strcmp((*head)->id, customer->id) == 0) //checks if ID already exists in the system
	{	
		if (print_validation_msg(customer, *head, socket, print_msg) == 1) //checks if names of customer and head are different.
		{
			free(customer); //frees customer, as ID is in the system under different name
			return 1;
		}
		if (compare_date(*head, customer) == *head)
		{
			customer->date.day = (*head)->date.day;
			customer->date.month = (*head)->date.month;
			customer->date.year = (*head)->date.year;
		}
		
		//Removes node
		Customer *temp = trail;
		customer->debt += trail->debt;
		*head = trail->next;
		free(temp);
	}

	while (run != NULL)
	{
		if (!strcmp(run->id, customer->id)) //checks if ID already exists in the system
		{
			if (print_validation_msg(customer, run, socket, print_msg) == 1) //checks if names of customer and head are different.
			{
				free(customer); //frees customer, as ID is in the system under different name
				return 1;
			}
			
			if (socket != -1)
				write_to_database(ptr, customer);
			
			if (compare_date(run, customer) == run)
			{
				customer->date.day = run->date.day;
				customer->date.month = run->date.month;
				customer->date.year = run->date.year;
			}

			//Removes node
			Customer *temp = run;
			customer->debt += run->debt;
			trail->next = run->next;
			free(temp);
		}
		trail = trail->next;
		run = run->next;
	}
	return 0;
}

void print_search_results(Customer *head, Customer *pivot, char *comp, COMPARE(customer, pivot), int socket, PRINT_CUST(cust, socket))
{
	/*Function Prints List in accordance with Query
	
	head: Customer. Head of List.
	pivot: Customer. struct bearing information from query.
	comp: char*. operator from query.
	comp_function: Customer. comparison function needed in order to judge if node conforms to query.*/
	
	if (head == NULL)
	{
		return;
	}

	Customer *run = head;

	while (run != NULL) //runs through Linked List
	{
		if (strcmp(comp, "*") == 0 || comp_function(pivot, run) == pivot)
		{
			if (strcmp(comp, "!=") == 0 || strcmp(comp, ">") == 0 || strcmp(comp, "*") == 0) // print the following if run is unequal to or greater than pivot value. Or print function was called in general.
				print_cust(run, socket);
		} 
		else if (strcmp(comp, "*") == 0 || comp_function(run, pivot) == run) 
		{
			if (strcmp(comp, "!=") == 0 || strcmp(comp, "<") == 0 || strcmp(comp, "*") == 0) // print the following if run is unequal to or lesser than pivot value. Or print function was called in general.
				print_cust(run, socket);
		}
		else 
		{
			if (strcmp(comp, "=") == 0 || strcmp(comp, "*") == 0) // print the following if run is equal to the pivot value. Or print function was called in general.
				print_cust(run, socket);
		}
		run = run->next;
	}
}

void free_list(Customer **head)
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
		if(!found)
			insert(head, customer);	//insert new node.
	}
	if (socket != -1)
		print_search_results(*head, NULL, "*", compare_debt, socket, print_cust);
}