#ifndef _GENERATE_LIST_H_
#define _GENERATE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper_functions.h"

void Screen(Customer *head, Customer *pivot, char *comp, COMPARE(customer, pivot), int socket, PRINT_CUST(cust, socket));

char *find_op(char *buf);

void Fill_Attributes(Customer *head, char *param, char *val, Customer **fill, int socket, PRINT_MSG(str, socket));

void search(Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket));

void set(Customer *head, char *buf, int socket, PRINT_MSG(str, socket));

void home_screen(FILE *ptr, Customer **head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(cust, socket));

void write_to_database(FILE *ptr, Customer *customer);

void Insert(Customer **head, Customer *customer);

void Delete(FILE *ptr, Customer **head, Customer **customer, int socket, PRINT_MSG(str, socket));

void Free_All(Customer **head);

void program(FILE *ptr, Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket));

#endif