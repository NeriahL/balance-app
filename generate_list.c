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
