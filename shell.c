#include "shell.h"

/**
 * main - the main function
 * @ac: number of command line arguments supplied
 * @av: array of comman line argument strings
 *
 * Return: (Success) 0 always
 * ------- (Fail) we drop out the looser :)
 */
int main(int ac, char **av)
{
	sh_t data;
	int pl;

	_memset((void *)&data, 0, sizeof(data));
	signal(SIGINT, signal_handler);

	if (ac >= 2)
	{
		index_cmd(&data);
		pl = non_interactive(&data, ac, av);
		if (pl < 0)
		{
			free_data(&data);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}

	interactive(&data, av);

	exit(EXIT_SUCCESS);
}

/**
 * read_line - read a line from the standard input
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int read_line(sh_t *data)
{
	/* char *csr_ptr, *end_ptr, *line; */
	size_t n = 0;
	int input;

	if (isatty(STDIN_FILENO))
		PRINT(PROMPT);

	input = getline(&(data->line), &n, stdin);
	if (input < 0)
		return (FAIL);

	return (0);
}
#define DELIMITER " \n\t\r\a\v"
/**
 * split_line - splits line to tokens
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int split_line(sh_t *data)
{
	char *token;
	size_t size = TOKENSIZE, new_size, i = 0;

	if (_strcmp(data->line, "\n") == 0)
		return (FAIL);
	data->args = malloc(size * sizeof(char *));
	if (data->args == NULL)
		return (FAIL);
	token = strtok(data->line, DELIMITER);
	if (token == NULL)
		return (FAIL);
	while (token)
	{
		data->args[i++] =  token;
		if (i + 2 >= size)
		{
			new_size = size * 2;
			data->args = _realloc(data->args, size * sizeof(char *),
					new_size * sizeof(char *));
			if (data->args == NULL)
				return (FAIL);
			size = new_size;
		}
		token = strtok(NULL, DELIMITER);
	}
	data->args[i] = NULL;
	return (0);
}
#undef DELIMITER
#define DELIMITER ":"
/**
 * parse_line - parses arguments to valid command
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int parse_line(sh_t *data)
{
	if (is_path_form(data) > 0)
		return (SUCCESS);
	if (is_builtin(data) > 0)
	{
		if (handle_builtin(data) < 0)
			return (FAIL);
		return (NEUTRAL);
	}
	is_short_form(data);
	return (SUCCESS);
}
#undef DELIMITER
/**
 * process_cmd - process command and execute process
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int process_cmd(sh_t *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(data->cmd, data->args, environ) < 0)
		data->error_msg = _strdup("not found\n");
			return (FAIL);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (0);
}
