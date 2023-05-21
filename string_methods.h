#ifndef _STRING_METHODS_H_
#define _STRING_METHODS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "structures.h"
#include "helper_functions.h"
#include "generate_list.h"

enum COMMAND{ SET, SELECT };

char *clean(char *str);

char *lowercase(char *name);

char *find_op(char *buf);

char ** parse_query_text(char *buf, int socket, enum COMMAND command);

#endif