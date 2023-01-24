#ifndef _HELPER_FUNCTIONS_H_
#define _HELPER_FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct Date
{
    int month;
	int day;
	int year;
} Date;

typedef struct Customer
{
	char first_name[11];
	char last_name[11];
	char id[265];
	char phone_number[11];
	Date date;
	int debt;

	struct Customer *next;
} Customer;

Customer *compare_date(Customer *c1, Customer *c2);

Customer *compare_debt(Customer *c1, Customer *c2);

Customer *compare_first_name(Customer *c1, Customer *c2);

Customer *compare_last_name(Customer *c1, Customer *c2);

Customer *compare_id(Customer *c1, Customer *c2);

Customer *compare_phone_number(Customer *c1, Customer *c2);

int validate_id(Customer *customer, Customer *compare);

void p_cust(Customer *cust);

char *clean(char *str);
#endif