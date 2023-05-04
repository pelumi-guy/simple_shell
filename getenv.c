#include "main.h"

/**
 * _getenv - a function that extracts a single environment variable
 * from the array of environment variables
 * Description:
 * @name: key of environment variable to get
 * Return: Pointer to location of found environment variable 
 * or NULL if not found.
 **/

char *_getenv(const char *name)
{
int i, j;
int status;

for (i = 0; environ[i] != NULL; i++)
{
status = 1;
for (j = 0; environ[i][j] != '='; j++)
{
if (name[j] != environ[i][j])
{
status = 0;
break;
}
}

if (status)
{
return (&environ[i][j + 1]);
}
}
return (NULL);
}

/**
 * setenv - 
 *
 *
 **/
