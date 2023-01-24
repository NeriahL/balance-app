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

int main()
{
	
	
	return 0;
}
