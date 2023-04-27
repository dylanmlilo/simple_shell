#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - function that creates a copy of the environment
 *
 * Return: NULL if an error occurs
 *         else a double pointer to the new copy.
 */

char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int i;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_environ[i])
		{
			for (i--; i >= 0; i--)
				free(new_environ[i]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[i], environ[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}

/**
 * free_env - function that frees the the environment copy
 */

void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * _getenv - function that gets an environmental variable from the PATH
 *
 * @var: name of the environmental variable to get
 *
 * Return: NULL if the environmental variable does not exist
 *         else a pointer to the environmental variable
 */

char **_getenv(const char *var)
{
	int i, length;

	length = _strlen(var);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], length) == 0)
			return (&environ[i]);
	}
	return (NULL);
}
