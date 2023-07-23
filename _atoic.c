#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	/* Check if the standard input is a terminal (interactive mode) */
	/*
	 * and if the read file descriptor (input file descriptor)
	 * is within 0-2 (standard file descriptors).
	 */
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	/*
	 * Loop through the delimiter string and check if
	 * the character 'c' matches any of the delimiters.
	 */
	/* If a match is found, return 1 (true). Otherwise, return 0 (false). */
	while (*delim)
	if (*delim++ == c)
		return (1)
	return (0);
}

/**
 * _isalpha - checks for an alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	/*
	 * Check if the input character 'c'
	 * is an uppercase or lowercase alphabet letter.
	 */

	/* If it is, return 1 (true), otherwise, return 0 (false). */

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	return (1);
	else
	return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 */
int _atoi(char *s)
{
		int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

		/*
		 * Loop through the input string 's' until the end
		 * ('\0') or until two flag checks have been done.
		 */
	for (i = 0; s[i] != '\0' && flag != 2; i++)
{
		/*
		 * Check if the current character is a minus sign
		 * ('-') and adjust the sign accordingly.
		*/
	if (s[i] == '-')
	sign *= -1;

	/* Check if the current character is a digit ('0' to '9'). */
	if (s[i] >= '0' && s[i] <= '9')
{
		flag = 1;
	/*
	 * Convert the character to an integer and
	 * add it to the result (taking care of multiple digits).
	 */
		result *= 10;
	result += (s[i] - '0');
	}
	else if (flag == 1)
		/*
		 * If a digit was previously found, and the current character
		 * is not a digit, set flag to 2 to exit the loop.
		 */
	flag = 2;
	}
	/* Apply the sign to the result to obtain the final output. */
if (sign == -1)
	output = -result;
	else
	output = result;
	return (output);
}
