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

	arg = strtok(command, " \t\n");
	while (arg != NULL)
	{
		argv[i] = arg; /* Add token to the argument list */
		i++;
		arg = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	/* Find the full path of the command using PATH */
	full_path = find_command(argv[0]);

	if (full_path == NULL)
	{
		printf("Command not found: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (execve(full_path, argv, NULL) == -1)
	{
		perror("shell"); /* Print an error if execve fails */
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid = create_child_process();

	if (pid == 0)
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
/**
 * find_command - Searches for the command in the PATH directories.
 * @command: The command to find.
 *
 * Return: The full path to the command if found, otherwise NULL.
 */
char *find_command(char *command)
{
	char *path = getenv("PATH");
	char *dir;
	char *full_path = (char *)malloc(BUFFER_SIZE * sizeof(char));

	/* Check if the command is already a full path */
	if (command[0] == '/')
	{
		/* Check if the full path is executable */
		if (access(command, X_OK) == 0)
		{
			return (strdup(command)); /* Return a copy of the full path */
		}
		return (NULL); /* Command is a full path, but not executable */
	}

	if (path == NULL || full_path == NULL)
	{
		perror("shell");
		exit(EXIT_FAILURE);
	}

	dir = strtok(path, ":");
	while (dir != NULL)
	{
		snprintf(full_path, BUFFER_SIZE, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}

		dir = strtok(NULL, ":");
	}

	free(full_path);
	return (NULL); /* Command not found in any PATH directory */
}

