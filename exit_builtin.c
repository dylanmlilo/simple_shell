#include "shell.h"

int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - function that matches a command with a corresponding
 *               shellby builtin function
 *
 * @command: the command to match
 *
 * Return: A function pointer to the corresponding builtin
 */

int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};

	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shellby_exit - function that causes normal process
 *                termination for the shellby shell
 *
 * @args: array of arguments
 * @front: double pointer to the beginning of args
 *
 * Return: (-3) if there are no arguments
 *         (-2) if the given exit value is invalid
 *         or exits with the given status value
 */

int shellby_exit(char **args, char **front)
{
	int i, length;
	unsigned int num = 0, max = 1 << (sizeof(int) * 7);

	i = 0, length = 10;

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			length++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= length && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * shellby_cd - function that changes the current
 *              directory of the shellby process
 *
 * @args: array of arguments
 * @front: double pointer to the beginning of args
 *
 * Return: (2) if the given string is not a directory
 *         (-1) if an error occurs
 *         else - 0
 */

int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line;
	char *init_pwd = NULL, *pwd = NULL;
	struct stat dir;

	new_line = "\n";

	init_pwd = getcwd(init_pwd, 0);
	if (!init_pwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
			    args[0][1] == '\0')
			{
				if (_getenv("INIT_PWD") != NULL)
					(chdir(*_getenv("INIT_PWD") + 7));
			}
			else
			{
				free(init_pwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
			    && ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(init_pwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "INIT_PWD";
	dir_info[1] = init_pwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(init_pwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shellby_help - function that displays information
 *                about shellby builtin commands
 *
 * @args: array of arguments
 * @front: pointer to the beginning of args
 *
 * Return: 0 (success) -1(failure)
 */

int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
