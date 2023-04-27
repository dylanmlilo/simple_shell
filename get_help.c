#include "shell.h"

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);

/**
 * get_args - function that gets a command from standard input
 *
 * @line: buffer to store the command
 * @exe_ret: return value of the last executed command
 *
 * Return: NULL if an error occurs
 *         else a pointer to the stored command
 */

char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - function that partitions operators
 *             from commands and calls them
 *
 * @args: array of arguments
 * @front: double pointer to the beginning of args
 * @exe_ret: return value of the parent process' last executed command
 *
 * Return: return value of the last executed command
 */

int call_args(char **args, char **front, int *exe_ret)
{
	int ret, i;

	if (!args[0])
		return (*exe_ret);
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
 * run_args - function that calls the execution of a command
 *
 * @args: array of arguments
 * @front: double pointer to the beginning of arguments
 * @exe_ret: return value of the parent process' last executed command
 *
 * Return: return value of the last executed command
 */

int run_args(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handle_args - function that gets, call
 *               and runs the execution of a command
 *
 * @exe_ret: return value of the parent process' last executed command
 *
 * Return: (-2) if an end-of-file is read
 *         (-1) if the input cannot be tokenized
 *         else the exit value of the last executed command
 */

int handle_args(int *exe_ret)
{
	int i, ret;
	char **args, *line = NULL, **front;

	ret = 0;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - function that checks if there are any
 *              leading ';', ';;', '&&', or '||'
 *
 * @args: 2D pointer to tokenized commands and arguments
 *
 * Return: 0 (success) 2 if a ';', '&&', or '||' (error)
 */

int check_args(char **args)
{
	size_t i;
	char *current, *next;

	for (i = 0; args[i]; i++)
	{
		current = args[i];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (i == 0 || current[1] == ';')
				return (create_error(&args[i], 2));

			next = args[i + 1];

			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
