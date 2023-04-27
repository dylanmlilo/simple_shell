#include "shell.h"

void sig_handler(int sig);
int execute(char **args, char **front);

/**
 * main - function that runs a simple UNIX command interpreter
 *
 * @argc: number of arguments
 * @argv: arguments vector
 *
 * Return: the return value of the last executed command
 */

int main(int argc, char *argv[])
{
	int ret, rein;
	int *exe_ret = &rein;
	char *prompt = "#cisfun$ ", *new_line = "\n";

	ret = 0;
	name = argv[0];
	aliases = NULL;
	hist = 1;
	signal(SIGINT, sig_handler);
	*exe_ret = 0;
	environ = _copyenv();

	if (!environ)
	{
		exit(-100);
	}

	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
		{
			ret = handle_args(exe_ret);
		}
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 10);
		ret = handle_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
			{
				write(STDOUT_FILENO, new_line, 10);
			}
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}
	free_env();
	free_alias_list(aliases);
	return (*exe_ret);
}

/**
 * sig_handler - function that prints a new prompt upon a signal
 * @sig: signal
 */

void sig_handler(int sig)
{
	char *new_prompt = "\n#cisfun$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 20);
}

/**
 * execute - function that executes a command in a child process
 *
 * @args: array of arguments
 * @front: double pointer to the beginning of arguments
 *
 * Return: A corresponding error code if an error occurs
 *         else the exit value of the last executed command
 */

int execute(char **args, char **front)
{
	pid_t child_pid;
	int flag, status, ret;
	char *command = args[0];

	flag = status = 0;

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if ((access(command, F_OK) == -1) || !command)
	{
		if (errno == EACCES)
		{
			ret = (create_error(args, 126));
		}
		else
		{
			ret = (create_error(args, 127));
		}
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
			{
				free(command);
			}
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
			{
				ret = (create_error(args, 126));
			}
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
	{
		free(command);
	}
	return (ret);
}
