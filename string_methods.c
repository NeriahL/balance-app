#include "string_methods.h"

char *lowercase(char *name)
{
	char str[strlen(name)];
	strcpy(str, name);
	int i = 0;
	while (str[i] != '\0')
	{
		str[i] = tolower(str[i]);
		i++;
	}
	char *point = str;
	return point;
}

char *clean(char *str)
{
	/*Function Clears Away Whitespace
	
	str: char*. */
	if (str == NULL)
		return NULL;
	
	while (*str == ' ' | *str == '\t' || *str == '\0' || *str == '\n') //moves beginning of string to after the leading whitespace
		str++;

	int i = strlen(str)-1;
	char new_arr[100];

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\0' || str[i] == '\n') //marks 'i' as end of new string and decreses its value until beginning of trailing whitespace
		i--;
	
	strncpy(new_arr, str, i+1); //copies clean string to newly allocated memory.
	new_arr[i+1] = '\0';
	str = new_arr; //points pointer at new string.

	return str;
}

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

char ** parse_query_text(char *buf)
{
	char **query = calloc(3, sizeof(char *));

	char cleaned1[100] = {0};
	char cleaned2[100] = {0};

	query[1] = find_op(buf);
	query[0] = strtok(buf, query[1]);
	query[2] = strtok(NULL, query[1]);

	if (query[0] != NULL)
	{
		strcpy(cleaned1, clean(query[0]));
		strcpy(query[0], cleaned1);
	}
	if (query[2] != NULL)
	{
		strcpy(cleaned2, clean(query[2]));
		strcpy(query[2], cleaned2);
	}

	return query;
}