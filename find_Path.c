#include "main.h"

/**
 * find_Path - a function that searches for the path of a command string
 * Description:
 * @cmd: input command
 * @searchPath: system path where command is found
 * @paths: array of environment set path strings 
 * Return: 0
 */

char *find_Path(char *cmd, char **paths)
{
	int i;
	char *searchPath;

	for (i = 0; paths[i]; i++)
        {
		if (access(cmd, F_OK) == 0)
		{
			searchPath = malloc(sizeof(char) * (strlen(cmd) + 1));
			strcpy(searchPath, cmd);
			return (searchPath);
		}
		searchPath = malloc(sizeof(char) * (strlen(paths[i]) + strlen(cmd) + 2));
                strcpy(searchPath, paths[i]);
                strcat(searchPath, "/");
                strcat(searchPath, cmd);
                if (access(searchPath, F_OK) == 0)
                {
                       // printf("command directory found: %s\n", searchPath);
                        return (searchPath);
                }
		else 
		{
			//printf("Wrong searchPath: %s\n", searchPath);
			free (searchPath);
		}
        }
	return (NULL);
}
