#include "shell.h"

/**
 * interactive - interactive shell
 * @data: data struct containing shell's state data
 * @av: array of comman line argument strings
 *
 * Return:
 */
void interactive(sh_t *data, char **av)
{
	int pl;

	while (1)
	{
		index_cmd(data);
		if (read_line(data) < 0)
		{
			if (isatty(STDIN_FILENO))
				PRINT("\n");
			return;
		}
		if (split_line(data) < 0)
		{
			free_data(data);
			continue;
		}
		pl = parse_line(data);
		if (pl == 0)
		{
			free_data(data);
			continue;
		}
		if (pl < 0)
		{
			print_error(data, av[0]);
			continue;
		}
		if (process_cmd(data) < 0)
		{
			print_error(data, av[0]);
			return;
		}
		free_data(data);
	}
	free_data(data);
}
