#ifndef _PROGRAM_FUNCTIONALITY_H_
#define _PROGRAM_FUNCTIONALITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "handle_commands.h"
#include "validations.h"
#include "generate_list.h"

void handle_options(FILE *ptr, Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket));

void populate_customer(Customer *head, char *param, char *val, Customer *customer, int socket, PRINT_MSG(str, socket));

void handlie_select(Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket));

void handle_set(Customer *head, char *buf, int socket, PRINT_MSG(str, socket));

#endif