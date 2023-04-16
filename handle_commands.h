#ifndef _PROGRAM_FUNCTIONALITY_H_
#define _PROGRAM_FUNCTIONALITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "handle_commands.h"
#include "validations.h"
#include "generate_list.h"

int (*select_compare_function(char * parameter))(Customer *, char *);

void handle_options(FILE *ptr, Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket));

int populate_customer(Customer *head, char *param, char *val, Customer *customer);

void handlie_select(Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket));

void handle_set(Customer *head, char *buf, int socket, PRINT_MSG(str, socket));

#endif