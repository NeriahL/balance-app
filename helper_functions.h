#ifndef _HELPER_FUNCTIONS_H_
#define _HELPER_FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "structures.h"
#include "string_methods.h"

int compare_date(Customer *cust, char *date);

int compare_debt(Customer *cust, char *debt);

int compare_first_name(Customer *cust, char *first_name);

int compare_last_name(Customer *cust, char *last_name);

int compare_id(Customer *cust, char *id);

int compare_phone_number(Customer *cust, char *phone_number);

#endif