#ifndef _VALIDATIONS_H_
#define _VALIDATIONS_H_

#include "structures.h"
#include "helper_functions.h"
#include "generate_list.h"

int same_id_different_name(Customer *customer, Customer *compare);

int id_is_valid(Customer *customer);

int validate_date(Customer *customer);

int print_validation_msg(Customer *customer, Customer *compare);

#endif