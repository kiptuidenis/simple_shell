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

	command[strcspn(command, "\n")] = '\0';

	pid = fork();  /* Fork a child process */
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		char *arg;
		char *argv[BUFFER_SIZE];
		int i = 0;

		arg = strtok(command, " \t\n");
		while (arg != NULL)
		{
			argv[i] = arg;  /* Add token to the argument list */
			i++;
			arg = strtok(NULL, " \t\n");
		}
		argv[i] = NULL;
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("./shell_0.2");  /* Print an error if execve fails */
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);
	}
}
