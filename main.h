#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

extern char **environ;

int _putchar(char c);
char *_getenv(const char *name);
char *find_Path(char *cmd, char **paths);
char **tokenize(char *str, char *delim, char **tokens);
void signal_handler(int signo);


#endif /* MAIN_H */
