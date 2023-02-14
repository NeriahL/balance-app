#ifndef _GENERATE_LIST_H_
#define _GENERATE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper_functions.h"
#include "string_methods.h"

void Screen(Customer *head, Customer *pivot, char *comp, COMPARE(customer, pivot), int socket, PRINT_CUST(cust, socket));

void write_to_database(FILE *ptr, Customer *customer);

void Insert(Customer **head, Customer *customer);

void Delete(FILE *ptr, Customer **head, Customer **customer, int socket, PRINT_MSG(str, socket));

void Free_All(Customer **head);

#endif