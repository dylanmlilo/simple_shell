#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);
char *error_126(char **args);
char *error_127(char **args);

/**
 * num_len - function that counts the digit length of a number
 *
 * @num: number to count its digits
 *
 * Return: the length of the digits
 */

int num_len(int num)
{
	unsigned int number;
	int length = 1;

	if (num < 0)
	{
		length++;
		number = num * -1;
	}
	else
	{
		number = num;
	}
	while (number > 9)
	{
		length++;
		number /= 10;
	}

	return (length);
}

/**
 * _itoa - function that converts an integer to a string
 *
 * @num: integer to convert
 *
 * Return: converted string
 */

char *_itoa(int num)
{
	char *buffer;
	int length = num_len(num);
	unsigned int number;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		number = num * -1;
		buffer[0] = '-';
	}
	else
	{
		number = num;
	}

	length--;
	do {
		buffer[length] = (number % 10) + '0';
		number /= 10;
		length--;
	} while (number > 0);

	return (buffer);
}

/**
 * create_error - function that writes a custom
 *                error message to stderr
 *
 * @args: array of arguments
 * @err: error value
 *
 * Return: error value
 */

int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}

/**
 * error_126 - function that creates an error
 *             message for permission denied failures
 *
 * @args: array of arguments passed to the command
 *
 * Return: error string
 */

char *error_126(char **args)
{
	char *error, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);

	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(history_str);
	return (error);
}

/**
 * error_127 - function that creates an error message
 *             for command not found failures
 *
 * @args: array of arguments passed to the command
 *
 * Return: error string
 */

char *error_127(char **args)
{
	char *error, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);

	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Not found\n");

	free(history_str);
	return (error);
}
