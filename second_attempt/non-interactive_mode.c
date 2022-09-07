#include "shell.h"

/**
 * non_interactive - Non-interactive mode handler.
 * @data: Struct containing shell's state data.
 * @ac: number of command line arguments supplied.
 * @av: array of command line arrgument strings
 *
 * Return: 0 (Success)
 */
int non_interactive(sh_t *data, int ac, char **av)
{
	int pl;

	if (parse_args(data, ac, av) < 0)
	{
		free_data(data);
		return (FAIL);
	}
	pl = parse_line(data);
	if (pl == 0)
	{
		free_data(data);
		return (FAIL);
	}
	if (pl < 0)
	{
		print_error(data, av[0]);
		return (FAIL);
	}
	if (process_cmd(data) < 0)
	{
		print_error(data, av[0]);
		return (FAIL);
	}
	free_data(data);
	return (0);
}


/**
 * parse_args - parses program arguments to shell commands
 * @data: a pointer to the struct of data
 * @ac: number of arguments passed to program
 * @av: null terminated array of argument strings
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int parse_args(sh_t *data, int ac, char **av)
{
	size_t size = ac + 1, i = 0, j;
	char **temp;

	data->args = malloc(size * sizeof(char *));
	temp  = malloc(size * sizeof(char *));
	if (data->args == NULL || temp == NULL)
		return (FAIL);

	while (av[i])
	{
		temp[i] =  av[i];
		i++;
	}
	temp[i] = NULL;

	for (i = 0, j = 1; temp[j]; i++, j++)
		data->args[i] = temp[j];
	data->args[i] = NULL;

	free(temp);

	return (0);
}
