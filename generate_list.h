#ifndef _GENERATE_LIST_H_
#define _GENERATE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "helper_functions.h"
#include "validations.h"
#include "string_methods.h"

void collect_errors(char *error);

void print_errors(PRINT_MSG(cust, socket), int socket);

void print_search_results(Customer *head, char *string, char *comp, COMPARE(customer, string), int socket, PRINT_CUST(cust, socket));

void write_to_database(FILE *ptr, Customer *customer);

void insert(Customer **head, Customer *customer);

int delete(FILE *ptr, Customer **head, Customer *customer, int socket);

void list_init(FILE *ptr, Customer **head, char *buf, int socket, PRINT_CUST(cust, socket));

void free_list(Customer **head);

#endif