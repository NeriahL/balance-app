#ifndef _GENERATE_LIST_H_
#define _GENERATE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper_functions.h"

void Insert(Customer **head, Customer *customer);

void Delete(Customer **head, Customer **customer);

void Free_All(Customer **head);

void Print(Customer *head, Customer *pivot, char *comp, Customer *(comp_function)(Customer *customer, Customer *pivot));

void Run_Attributes(Customer *head, char *command, char *param, char *val, char *op, Customer **fill);

void write_to_database(FILE *ptr, Customer *customer);

void generate_node(Customer **head, char *buf, char *command, FILE *ptr);

#endif