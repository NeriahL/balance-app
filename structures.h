#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#define COMPARE(customer, string) int (comp_function)(Customer *customer, char *string)
#define PRINT_CUST(cust, socket) void (print_cust)(Customer *cust, int socket)
#define PRINT_MSG(str, socket) void (print_msg)(char str[], int socket)

enum COMPARISON
{
	EQUAL,
	GREATER,
	LESSER,
	NOT_EQUAL
};

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
	char id[10];
	char phone_number[11];
	Date date;
	int debt;

	struct Customer *next;
} Customer;

#endif