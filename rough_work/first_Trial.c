#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sys/wait.h"
#include <unistd.h>
#include "main.h"

/**
 * main - main block
 * Description:
 * Return: 0
 */

extern char **environ;

void read_command(char **toks, char *cmd, char **par);

int main(int ac, char **av, char **env)
{
	int i, j, status;
	ssize_t input;
	char *line = NULL;
	char *token, **tokens, *searchPath, *path, *paths[100];
	size_t n = 0;
	char delim[] = "\n ";
	char cmd[20], command[100], *parameters[20];
	pid_t child_pid, ppid = getpid();

	/* char *envp[] = { (char *) "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", 0 };*/
	path = _getenv("PATH");
	tokenize(path, ":", paths);
	//signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while(1)
	{	
		i = 0;
		printf("#welcome to the matrix$");
		//signal(SIGINT, signal_handler);	
		input = getline(&line, &n, stdin);
		if (input < 0)
		{
			printf("End of file caught\n");
			break;
			//kill(ppid, 9);	
		}
		else if (strcmp(line, "\n") == 0)
			continue;
//		if (strcmp(line, "exit\n") == 0)
//			break;
		
		tokens = malloc(sizeof(char *) * input);
//		printf("You have entered: %s and I'd graciously tokenise it for you below.\n", line);	
		token = strtok(line, delim);
		while (token)
		{
			tokens[i++] = token;
			token = strtok(NULL, delim);
		}
		tokens[i] = NULL;
		read_command(tokens, cmd, parameters);

		if (strcmp(cmd, "exit") == 0)
			break;
		
		searchPath = find_Path(cmd, paths);
		if (searchPath)
		{
//			printf("Command path: %s\n", searchPath);
//			for (i = 0; parameters[i]; i++)
//				printf("parameter[%d]: %s\n", i, parameters[i]);

			child_pid = fork();
			if (child_pid == 0)
				execve(searchPath, parameters, environ);
			else
				wait(&status);
		}
		
	}
	free (tokens);
	
	return(0);
}

void read_command(char **toks, char *cmd, char **par)
{
	int i = 0;
	strcpy(cmd, toks[i]);

	for (; toks[i]; i++)
		par[i] = toks[i];
	
	par[i] = '\0';
}

void signal_handler(int signo)
{
        pid_t ppid = getpid();
//	if (signo == SIGINT)
//	{
//	                printf("\n#welcome to the matrix$");
//      }
        if (signo == SIGQUIT)
        {
                printf("ppid: %i\n", ppid);
                kill(ppid, 9);
        }
}
