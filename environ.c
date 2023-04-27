#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - function that prints the current environment
 *
 * @args: array of arguments
 * @front: double pointer to the beginning of args
 *
 * Return: 0 (success) -1 (error)
 */

int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int i;
	char nl = '\n';

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &nl, 1);
	}
	(void)args;
	return (0);
}

/**
 * shellby_setenv - function that changes or adds
 *                  an environmental variable to the PATH
 *
 * @args: array of arguments passed to the shell
 * @front: double pointer to the beginning of args
 *
 * Return: 0 (success) -1 (failure)
 */

int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_variable = NULL, **new_environ, *new_val;
	size_t size;
	int i;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
		return (create_error(args, -1));
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	env_variable = _getenv(args[0]);
	if (env_variable)
	{
		free(*env_variable);
		*env_variable = new_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_val);
		return (create_error(args, -1));
	}

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	free(environ);
	environ = new_environ;
	environ[i] = new_val;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - function that deletes an environmental
 *                    variable from the PATH
 *
 * @args: array of arguments
 * @front: double pointer to the beginning of the arguments
 *
 * Return: 0 (success) -1 (failure)
 */

int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_variable, **new_environ;
	size_t size;
	int i, j;

	if (!args[0])
		return (create_error(args, -1));
	env_variable = _getenv(args[0]);

	if (!env_variable)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (i = 0, i = 0; environ[i]; i++)
	{
		if (*env_variable == environ[i])
		{
			free(*env_variable);
			continue;
		}
		new_environ[j] = environ[i];
		j++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
