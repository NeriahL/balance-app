#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_methods.h"

char *find_op(char *buf)
{
	char *op;

	if (strstr(buf, "!="))
		op = "!=\0";
		
	else if (strstr(buf, "<"))
		op = "<\0";
		
	else if (strstr(buf, ">"))
		op = ">\0";
		
	else if (strstr(buf, "="))
		op = "=\0";
		
	else
		op = "-\0";

	return op;
}

int main()
{
    char *buf = "first name\n";
    
    char *op = find_op(buf);

    printf("%s ", op);
    return 0;
}
