#ifndef _VALIDATIONS_H_
#define _VALIDATIONS_H_

#include "helper_functions.h"

int same_id_different_name(Customer *customer, Customer *compare);

int id_is_valid(Customer *customer);

int validate_date(Customer *customer);

int print_validation_msg(Customer *customer, Customer *compare, int socket, PRINT_MSG(str, socket));

#endif