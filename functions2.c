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
	printf("$ "); /* Display a simple prompt */
}

/**
 * print_environment - Prints the current environment variables.
 */
void print_environment(void)
{
	char **env_ptr;

	if (environ == NULL)
	{
		printf("Environment not available.\n");
		return;
	}

	env_ptr = environ;
	while (*env_ptr != NULL)
	{
		printf("%s\n", *env_ptr);
		env_ptr++;
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
