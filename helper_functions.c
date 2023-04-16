#include "helper_functions.h"
#include "generate_list.h"

int compare_date(Customer *cust, char *date)
{
	int day = 0, month = 0, year = 0, string_date = 0, cust_date = 0;

	sscanf(date, "%d/%d/%d", &month, &day, &year);

	string_date = (month*31) + (year*372) + day;
	cust_date = (cust->date.month*31) + (cust->date.year*372) + cust->date.day;

	 if (string_date > cust_date)
		return GREATER;
	else if (string_date < cust_date)
		return LESSER;
	else if (string_date == cust_date)
		return EQUAL;
}

int compare_debt(Customer *cust, char *debt)
{	
	int string_debt = 0, cust_debt = 0;
	
	string_debt = atoi(debt);
	cust_debt = cust->debt;

	 if (string_debt > cust_debt)
		return GREATER;
	else if (string_debt < cust_debt)
		return LESSER;
	else if (string_debt == cust_debt)
		return EQUAL;
}

int compare_first_name(Customer *cust, char *first_name)
{
	char cust_first[strlen(cust->first_name)];
	strcpy(cust_first, lowercase(clean(cust->first_name)));

	first_name = lowercase(clean(first_name));

	if (strcmp(first_name, cust_first) > 0)
		return GREATER;
	else if (strcmp(first_name, cust_first) < 0)
		return LESSER;
	else if(!strcmp(first_name, cust_first))
		return EQUAL;
}

int compare_last_name(Customer *cust, char *last_name)
{
	char cust_last[strlen(cust->last_name)];
	strcpy(cust_last, lowercase(clean(cust->last_name)));

	last_name = lowercase(clean(last_name));

	if (strcmp(last_name, cust_last) > 0)
		return GREATER;
	else if (strcmp(last_name, cust_last) < 0)
		return LESSER;
	else if(!strcmp(last_name, cust_last))
		return EQUAL;
}

int compare_id(Customer *cust, char *id)
{
	if (strcmp(id, cust->id) > 0)
		return GREATER;	 
	else if (strcmp(id, cust->id) < 0)
		return LESSER;
	else if (!strcmp(id, cust->id))
		return EQUAL;
	
}

int compare_phone_number(Customer *cust, char *phone_number)
{
	if (strcmp(phone_number, cust->phone_number) > 0)
		return GREATER;	 
	else if (strcmp(phone_number, cust->phone_number) < 0)
		return LESSER;
	else if (!strcmp(phone_number, cust->phone_number))
		return EQUAL;
}
 