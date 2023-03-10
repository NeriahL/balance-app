#ifndef _HELPER_FUNCTIONS_H_
#define _HELPER_FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define COMPARE(customer, pivot) Customer *(comp_function)(Customer *customer, Customer *pivot)
#define PRINT_CUST(cust, socket) void (print_cust)(Customer *cust, int socket)
#define PRINT_MSG(str, socket) void (print_msg)(char str[], int socket)

typedef struct Date
{
    int month;
	int day;
	int year;
} Date;

typedef struct Customer
{
	char first_name[12];
	char last_name[12];
	char id[265];
	char phone_number[11];
	Date date;
	int debt;

	struct Customer *next;
} Customer;

char *lowercase(char *name);

Customer *compare_date(Customer *c1, Customer *c2);

Customer *compare_debt(Customer *c1, Customer *c2);

Customer *compare_first_name(Customer *c1, Customer *c2);

Customer *compare_last_name(Customer *c1, Customer *c2);

Customer *compare_id(Customer *c1, Customer *c2);

Customer *compare_phone_number(Customer *c1, Customer *c2);

int validate_id(Customer *customer, Customer *compare, int socket, PRINT_MSG(str, socket));

char *clean(char *str);

int id_length(Customer *customer, int socket, PRINT_MSG(str, socket));

int validate_date(Customer *customer, int socket, PRINT_MSG(str, socket));

#endif