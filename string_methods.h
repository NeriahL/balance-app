#ifndef _STRING_METHODS_H_
#define _STRING_METHODS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

char *clean(char *str);

char *lowercase(char *name);

char *find_op(char *buf);

char ** parse_query_text(char *buf);

#endif