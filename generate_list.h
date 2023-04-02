#ifndef _GENERATE_LIST_H_
#define _GENERATE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper_functions.h"
#include "validations.h"
#include "string_methods.h"

void print_search_results(Customer *head, Customer *pivot, char *comp, COMPARE(customer, pivot), int socket, PRINT_CUST(cust, socket));

void write_to_database(FILE *ptr, Customer *customer);

void insert(Customer **head, Customer *customer);

int delete(FILE *ptr, Customer **head, Customer *customer, int socket, PRINT_MSG(str, socket));

void list_init(FILE *ptr, Customer **head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(cust, socket));

void free_list(Customer **head);

#endif