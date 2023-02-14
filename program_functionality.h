#ifndef _PROGRAM_FUNCTIONALITY_H_
#define _PROGRAM_FUNCTIONALITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper_functions.h"

void program(FILE *ptr, Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket));

void Fill_Attributes(Customer *head, char *param, char *val, Customer **fill, int socket, PRINT_MSG(str, socket));

void search(Customer *head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(str, socket));

void set(Customer *head, char *buf, int socket, PRINT_MSG(str, socket));

void home_screen(FILE *ptr, Customer **head, char *buf, int socket, PRINT_CUST(cust, socket), PRINT_MSG(cust, socket));

#endif