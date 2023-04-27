#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - function frees up memory taken by args
 *
 * @args: null-terminated double pointer containing arguments
 * @front: double pointer to the beginning of the arguments
 *
 * Return: Nothing
 */

void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - function that gets the current PID
 *
 * Return: current process ID (success) NULL (failure)
 */

char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - function that gets the value corresponding
 *                 to an environmental variable
 *
 * @beginning: environmental variable to search for
 * @len: length of the environmental variable to search for
 *
 * Return: If the variable is not found - an empty string
 *         Otherwise - the value of the environmental variable
 */

char *get_env_value(char *beginning, int len)
{
	char **var_address;
	char *replacement = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_address = _getenv(var);
	free(var);
	if (var_address)
	{
		tmp = *var_address;
		while (*tmp != '=')
			tmp++;
		tmp++;
		replacement = malloc(_strlen(tmp) + 1);
		if (replacement)
			_strcpy(replacement, tmp);
	}
	return (replacement);
}

/**
 * variable_replacement - function that handles variable replacement
 *
 * @line: double pointer containing the command and arguments
 * @exe_ret: pointer to the return value of the last executed command
 *
 * Return: Nothing
 */

void variable_replacement(char **line, int *exe_ret)
{
	int i, j, length;
	char *replacement = NULL, *init_line = NULL, *new_line;

	j = 0;

	init_line = *line;
	for (i = 0; init_line[i]; i++)
	{
		if (init_line[i] == '$' && init_line[i + 1] &&
		    init_line[i + 1] != ' ')
		{
			if (init_line[j + 1] == '$')
			{
				replacement = get_pid();
				j = i + 2;
			}
			else if (init_line[i + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				j = i + 2;
			}
			else if (init_line[i + 1])
			{
				for (j = i + 1; init_line[j] &&
					     init_line[j] != '$' &&
					     init_line[j] != ' '; j++)
					;
				length = j - (i + 1);
				replacement = get_env_value(&init_line[i + 1], length);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&init_line[j]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, init_line, i);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &init_line[j]);
			_strcat(new_line, &init_line[j]);
			free(init_line);
			*line = new_line;
			init_line = new_line;
			i = -1;
		}
	}
}
