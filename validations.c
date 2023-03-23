#include "validations.h"

int same_id_different_name(Customer *customer, Customer *compare, int socket, PRINT_MSG(str, socket))
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

int id_is_valid(Customer *customer, int socket, PRINT_MSG(str, socket))
{
	char out[400];
	if (strlen(customer->id) != 9 || atoi(customer->id) == 0) // validate ID as being 9 digits and numerical.
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
