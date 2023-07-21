#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *command;

	while (1)
	{
		display_prompt();  /* Display the prompt */

		command = read_command();  /* Read the command line */

		if (command == NULL)
		{
			printf("\n");
			break;  /* Exit the shell if end of file
				 *(Ctrl+D) is encountered
				 */
		}

		if (*command != '\0')  /* Check if the command is not empty */
			execute_command(command);  /* Execute the command */

		free(command);  /* Free the allocated memory */
	}

	return (0);
}

/**
 * display_prompt - Displays a simple prompt.
 */
void display_prompt(void)
{
	printf("#cisfun$ "); /* Display a simple prompt */
}

