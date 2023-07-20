#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * display_prompt - Displays a simple prompt.
 */
void display_prompt(void)
{
	printf("#cisfun$ ");  /* Display a simple prompt */
}

/**
 * read_command - Reads a command line from stdin.
 *
 * Return: The command line string.
 */
char *read_command(void)
{
	char *command = NULL;
	size_t buffer_size = 0;

	ssize_t num_chars = getline(&command, &buffer_size, stdin);

	if (num_chars == -1)
	{
		free(command);
		return (NULL);
	}

	return (command);
}

/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid;

	command[strcspn(command, "\n")] = '\0';  /* Remove the trailing newline
						  *character
						  */

	pid = fork();  /* Fork a child process */
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		char *argv[2];

		argv[0] = command;
		argv[1] = NULL;

		execve(command, argv, NULL);  /* Execute the command without
					       *handling PATH
					       */
		perror("./shell");  /* Print an error if execve fails */
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);  /* Wait for the child process
					    *to finish
					    */
	}
}
