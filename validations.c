#include "validations.h"

int same_id_different_name(Customer *customer, Customer *compare)
{
	/*Function validates if ID is already present in the system
	
	customer: Customer.
	compare: Customer.
	
	return: Function returns 1 if first and last names are not equal between two Customers.
	
	used to validate ID*/

	if (compare != NULL)
	{
		char cust_first[12];
		char cust_last[12];
		char comp_first[12];
		char comp_last[12];
		char cust_id[10];
		char comp_id[10];

		strcpy(cust_first, lowercase(customer->first_name));
		strcpy(cust_last, lowercase(customer->last_name));
		strcpy(comp_first, lowercase(compare->first_name));
		strcpy(comp_last, lowercase(compare->last_name));
		strcpy(cust_id, customer->id);
		strcpy(comp_id, compare->id);


		if((strcmp(cust_first, comp_first) != 0 || strcmp(cust_last, comp_last) != 0))
			return 1;
	}
	return 0;
}

int id_is_valid(Customer *customer)
{
	if (strlen(customer->id) != 9 || atoi(customer->id) == 0) // validate ID as being 9 digits and numerical.
		return 0;
	
	return 1;
}

int validate_date(Customer *customer)
{
	if ((customer->date.day > 31 || customer->date.day < 1) || 
		(customer->date.month > 12 || customer->date.month < 1) || 
		(customer->date.year > 2023))								// validate that date is legal, if non-valid, free *fill.
		return 0;
	return 1;
}

int print_validation_msg(Customer *customer, Customer *compare)
{
	char out[400];
	int r_value = 0;

	if(validate_date(customer) == 0)
	{
		sprintf(out, "Error: Customer %s %s has been entered with incorrect date",
				customer->first_name,
				customer->last_name);
		r_value = 1;
		collect_errors(out);
	}
	if (id_is_valid(customer) == 0)
	{
		sprintf(out ,"Error: Customer %s %s has been entered with incorrect ID %s",
				customer->first_name,
				customer->last_name,
				customer->id);
		r_value = 1;
		collect_errors(out);
	}
	if(same_id_different_name(customer, compare) == 1)
	{
		strcpy(out, "Error: Name of customer does not match name paired to ID in system.Please enter correct name and/or ID number");
		r_value = 1;
		collect_errors(out);
	}
	else
		return 0;
	return r_value;
}
