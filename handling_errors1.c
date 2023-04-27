#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);

/**
 * error_env - function that creates an error
 *             message for shellby_env errors
 *
 * @args: array of arguments passed to the command
 *
 * Return: the error string
 */

char *error_env(char **args)
{
	char *error, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);

	args--;
	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 45;
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
	_strcat(error, ": Unable to edit environment\n");

	free(history_str);
	return (error);
}

/**
 * error_1 - function that creates an error
 *           message for shellby_alias errors
 *
 * @args: array of arguments passed to the command
 *
 * Return: error string
 */

char *error_1(char **args)
{
	char *error;
	int length;

	length = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " Not found\n");

	return (error);
}

/**
 * error_2_exit - function that creates an error
 *                message for shellby_exit errors
 *
 * @args: array of arguments passed to the command
 *
 * Return: error string
 */

char *error_2_exit(char **args)
{
	char *error, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);

	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": exit: illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(history_str);
	return (error);
}

/**
 * error_2_cd - function that creates an error
 *              message for shellby_cd errors
 *
 * @args: array of arguments passed to the command
 *
 * Return: error string
 */

char *error_2_cd(char **args)
{
	char *error, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';

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
	if (args[0][0] == '-')
		_strcat(error, ": cd: illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(history_str);
	return (error);
}

/**
 * error_2_syntax - function that creates an error
 *                  message for syntax errors
 *
 * @args: array of arguments passed to the command
 *
 * Return: error string
 */

char *error_2_syntax(char **args)
{
	char *error, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);

	length = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected input\n");

	free(history_str);
	return (error);
}
