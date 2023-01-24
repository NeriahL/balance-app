#include "helper_functions.h"

Customer *compare_date(Customer *c1, Customer *c2)
{
	/*Function Compares dates:
		c1: Customer.
		c2: Customer.
		c1_date: int, calculates number of days in date for c1.
		c2_date: int, calculates number of days in date for c2.
		
		return: the Customer with the greater date.*/
    Customer *ptr;
    int c1_date = (c1->date.year *372) + (c1->date.month * 31) + c1->date.day;
    int c2_date = (c2->date.year *372) + (c2->date.month * 31) + c2->date.day;

    if (c1_date > c2_date)
    {
        ptr = c1;
    }
    else
    {
        ptr = c2;
    }

    return ptr;
}

Customer *compare_debt(Customer *c1, Customer *c2)
{	
	/*Function Compares debts:
		c1: Customer.
		c2: Customer.
		
		return: the Customer with the greater debt.*/
    Customer *r_cust;

    if (!c1 || !c2)
    {
        return NULL;
    }
    
    if (c1->debt < c2->debt)
        r_cust = c1;
    else 
        r_cust = c2;
    
    return r_cust;
}

Customer *compare_first_name(Customer *c1, Customer *c2)
{
	/*Function Compares first names:
		c1: Customer.
		c2: Customer.
		
		return: the Customer with the greater valued first name.*/
    Customer *r_cust;

    if (strcmp(c1->first_name, c2->first_name) > 0)
        r_cust = c1;
    else 
        r_cust = c2;

    return r_cust;
}

Customer *compare_last_name(Customer *c1, Customer *c2)
{
	/*Function Compares last names:
		c1: Customer.
		c2: Customer.
		
		return: the Customer with the greater valued last name.*/
    Customer *r_cust;

    if (strcmp(c1->last_name, c2->last_name) > 0)
        r_cust = c1;
    else 
        r_cust = c2;
        
    return r_cust;
}

Customer *compare_id(Customer *c1, Customer *c2)
{
	/*Function Compares ids:
		c1: Customer.
		c2: Customer.
		
		return: the Customer with the greater valued id.*/
    Customer *r_cust = NULL;

	if (strcmp(c1->id, c2->id) > 0)
		r_cust = c1;
	else
		r_cust = c2;
    
	return r_cust;
}

Customer *compare_phone_number(Customer *c1, Customer *c2)
{
	/*Function Compares phone numbers:
		c1: Customer.
		c2: Customer.
		
		return: the Customer with the greater valued phone numbers.*/
    Customer *r_cust;
    if (atoi(c1->phone_number)> atoi(c2->phone_number))
        r_cust = c1;
    else
        r_cust = c2;
    
    return r_cust;
}

int validate_id(Customer *customer, Customer *compare)
{
	/*Function validates if ID is already present in the system
	
	customer: Customer.
	compare: Customer.
	
	return: Function returns 1 if first and last names are not equal between two Customers.
	
	used to validate ID*/
	if (compare != NULL)
	{
		if(strcmp(compare->first_name, customer->first_name) != 0 ||
		   strcmp(compare->last_name, customer->last_name) != 0)
		{
			printf("Error: Name of customer does not match name paired to ID in system.\nPlease enter correct name and/or ID number\n");
			return 1;
		}
	}
	return 0;
}
