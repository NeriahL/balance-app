#ifndef _VALIDATIONS_H_
#define _VALIDATIONS_H_

#include "helper_functions.h"

int same_id_different_name(Customer *customer, Customer *compare, int socket, PRINT_MSG(str, socket));

int id_is_valid(Customer *customer, int socket, PRINT_MSG(str, socket));

int validate_date(Customer *customer, int socket, PRINT_MSG(str, socket));

#endif