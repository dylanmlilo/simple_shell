#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - function that displays all possible builtin shellby commands
 */

void help_all(void)
{
	char *message = "Shellby\nThese shell commands are defined internally\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "Type 'help' to see this list\nType 'help name' to find ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "out more about the function 'name'\n\n  alias   \t";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * help_alias - function that displays information on
 *              the shellby builtin command 'alias'
 */

void help_alias(void)
{
	char *message = "alias: alias [[NAME ='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n\talias: prints a list of all aliases, one per line, in ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "the format NAME = 'VALUE'\n\talias name [name2...]:prints";

	write(STDOUT_FILENO, message, _strlen(message));
	message = " the aliases name, name2, etc, one per line, in the ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "form NAME = 'VALUE'\n\talias NAME = 'VALUE' [...]: Defines";

	write(STDOUT_FILENO, message, _strlen(message));
	message = " an alias for each NAME whose VALUE is given. If NAME ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "is already an alias, replace its value with VALUE\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * help_cd - function that displays information on
 *           the shellby builtin command 'cd'
 */

void help_cd(void)
{
	char *message = "cd: cd [DIRECTORY]\n\tchanges the current directory of the";

	write(STDOUT_FILENO, message, _strlen(message));
	message = " process to DIRECTORY.\n\n\tIf no argument is given, the ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "command is interpreted as cd $HOME. If the argument '-' is";

	write(STDOUT_FILENO, message, _strlen(message));
	message = " given, the command is interpreted as cd $OLDPWD.\n\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "\tThe environment variables PWD and INITIAL_PWD are updated ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "after a change of directory.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * help_exit - function that displays information
 *             on the shellby builtin command 'exit'
 */

void help_exit(void)
{
	char *message = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "STATUS argument is the integer used to exit the shell.";

	write(STDOUT_FILENO, message, _strlen(message));
	message = " If no argument is given, the command is interpreted as";

	write(STDOUT_FILENO, message, _strlen(message));
	message = " exit 0.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * help_help - function that displays information on
 *             the shellby builtin command 'help'
 */

void help_help(void)
{
	char *message = "help: help\n\tSee all possible Shellby builtin commands\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n      help [BUILTIN NAME]\n\tsee specific information on each ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "builtin command.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}
