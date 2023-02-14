#ifndef _VALIDATIONS_H_
#define _VALIDATIONS_H_

#include "helper_functions.h"

int validate_id(Customer *customer, Customer *compare, int socket, PRINT_MSG(str, socket));

int id_length(Customer *customer, int socket, PRINT_MSG(str, socket));

int validate_date(Customer *customer, int socket, PRINT_MSG(str, socket));

#endif