#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"


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

	if (num_chars > 0 && command[num_chars - 1] == '\n')
		command[num_chars - 1] = '\0';

	return (command);
}

/**
 * create_child_process - Creates a child process.
 *
 * Return: The PID of the child process.
 */
pid_t create_child_process(void)
{
	pid_t pid;

	pid = fork(); /* Fork a child process */
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	return (pid);
}

/**
 * free_tokens - Frees the memory allocated for each token.
 * @argv: The argument list containing tokens.
 * @count: The number of tokens in the argument list.
 */
void free_tokens(char **argv, int count)
{
	int j;

	for (j = 0; j < count; j++)
	{
		free(argv[j]);
	}
}

/**
 * run_command - Executes a command inside the child process.
 * @command: The command to execute.
 */
void run_command(char *command)
{
	char *arg;
	char *argv[BUFFER_SIZE];
	int i = 0;
	char *full_path;

	command[strcspn(command, "\n")] = '\0';
	if (command[strlen(command) - 1] == '\n')
		command[strlen(command) - 1] = '\0';

	arg = strtok(command, " \t\n");
	while (arg != NULL)
	{
		argv[i] = strdup(arg); /* Add token to the argument list */
		i++;
		arg = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	free(command);

	/* Find the full path of the command using PATH */
	full_path = find_command(argv[0]);

	if (full_path == NULL)
	{
		printf("Command not found: %s\n", argv[0]);
		free_tokens(argv, i);
		exit(EXIT_FAILURE);
	}

	if (execve(full_path, argv, NULL) == -1)
	{
		perror("shell"); /* Print an error if execve fails */
		free_tokens(argv, i);
		exit(EXIT_FAILURE);
	}

	free_tokens(argv, i);
}


/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid = create_child_process();

	if (command[strlen(command) - 1] == '\n')
		command[strlen(command) - 1] = '\0';

	if (strcmp(command, "exit") == 0 || strcmp(command, "exit\n") == 0)
	{
		free(command);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "env") == 0 || strcmp(command, "env\n") == 0)
	{
		print_environment();
	}
	else if (pid == 0)
	{
		/* Child process */
		run_command(command);
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);
	}
}

