#include "main.h"

/**
* tokenize - a function to tokenize a string
* Description:
* @str: String to be tokenized
* @delim: delimiter to use
* @tokens: pointer to array of returned tokens
* Return: Array of token strings
**/

char **tokenize(char *str, char *delim, char **tokens)
{
        int i = 0;
        char *token;

        token = strtok(str, delim);
        while (token)
        {
                tokens[i++] = token;
                token = strtok(NULL, delim);
        }
        tokens[i] = '\0';
        return (tokens);
}
