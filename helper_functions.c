#include "helper_functions.h"
#include "generate_list.h"

char *lowercase(char *name)
{
	char str[strlen(name)];
	strcpy(str, name);
	int i = 0;
	while (str[i] != '\0')
	{
		str[i] = tolower(str[i]);
		i++;
	}
	char *point = str;
	return point;
}

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
        ptr = c1;
    else
        ptr = c2;

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
        return NULL;
    
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

	char c1_first[strlen(c1->first_name)];
	strcpy(c1_first, lowercase(c1->first_name));

	char c2_first[strlen(c2->first_name)];
	strcpy(c2_first, lowercase(c2->first_name));

    Customer *r_cust;

    if (strcmp(c1_first, c2_first) > 0)
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

	char c1_last[strlen(c1->last_name)];
	strcpy(c1_last, lowercase(c1->last_name));
	
	char c2_last[strlen(c2->last_name)];
	strcpy(c2_last, lowercase(c2->last_name));

    
	Customer *r_cust;

    if (strcmp(c1_last, c2_last) > 0)
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

int validate_id(Customer *customer, Customer *compare, int socket, PRINT_MSG(str, socket))
{
	/*Function validates if ID is already present in the system
	
	customer: Customer.
	compare: Customer.
	
	return: Function returns 1 if first and last names are not equal between two Customers.
	
	used to validate ID*/

	if (compare != NULL)
	{
		char *out = "Error: Name of customer does not match name paired to ID in system.\nPlease enter correct name and/or ID number\n";
		char cust_first[12];
		char cust_last[12];
		char comp_first[12];
		char comp_last[12];

		strcpy(cust_first, lowercase(customer->first_name));
		strcpy(cust_last, lowercase(customer->last_name));
		strcpy(comp_first, lowercase(compare->first_name));
		strcpy(comp_last, lowercase(compare->last_name));

		if(strcmp(cust_first, comp_first) != 0 || strcmp(cust_last, comp_last) != 0)
		{
			if (socket != 0)
			{
				print_msg(out, socket);
			}
			return 1;
		}
	}
	return 0;
}

char *clean(char *str)
{
	/*Function Clears Away Whitespace
	
	str: char*. */
	if (str == NULL)
		return NULL;
	
	while (*str == ' ' | *str == '\t' || *str == '\0' || *str == '\n') //moves beginning of string to after the leading whitespace
		str++;

	int i = strlen(str)-1;
	char new_arr[100];

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\0' || str[i] == '\n') //marks 'i' as end of new string and decreses its value until beginning of trailing whitespace
		i--;
	
	strncpy(new_arr, str, i+1); //copies clean string to newly allocated memory.
	new_arr[i+1] = '\0';
	str = new_arr; //points pointer at new string.

	return str;
}

int id_length(Customer *customer, int socket, PRINT_MSG(str, socket))
{
	char out[400];
	if (strlen(customer->id) != 9 || atoi(customer->id) == 0) // validate ID as being 9 digits and numerical. if non-valid, free *fill.
	{
		sprintf(out ,"Customer %s %s has been entered with incorrect ID %s\n",
				customer->first_name,
				customer->last_name,
				customer->id);
		print_msg(out, socket);
		
		return 0;
	}
	return 1;
}

int validate_date(Customer *customer, int socket, PRINT_MSG(str, socket))
{
	char out[400];

	if ((customer->date.day > 31 || customer->date.day < 1) || 
					(customer->date.month > 12 || customer->date.month <1) || 
					(customer->date.year > 2023))								// validate that date is legal, if non-valid, free *fill.
	{
		sprintf(out, "Customer %s %s has been entered with incorrect date\n",
				customer->first_name,
				customer->last_name);
		print_msg(out, socket);
		return 0;
	}
	return 1;
}
