#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * main - Entry point of the program.
 *@argc: argument count
 *@argv: array of strings
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	char *command;
	int interactive_mode = isatty(STDIN_FILENO);
	(void)argc;
	(void)argv;

	if (interactive_mode)
	{
		while (1)
		{
			display_prompt();  /* Display the prompt */
			command = read_command();  /* Read the command line */
			if (command == NULL)
			{
				printf("\n");
				return (0);  /* Exit the shell if end of file (Ctrl+D) is encountered */
			}

			if (*command != '\0')  /* Check if the command is not empty */
				execute_command(command);  /* Execute the command */

			free(command);  /* Free the allocated memory */
		}
	}
	else
	{
		/* Non-interactive mode, read from standard input (e.g., pipe or file) */
		command = read_command();
		while (command != NULL)
		{
			if (*command != '\0')  /* Check if the command is not empty */
				execute_command(command);  /* Execute the command */

			free(command);  /* Free the allocated memory */
			command = read_command();
		}
	}
	return (0);
}

