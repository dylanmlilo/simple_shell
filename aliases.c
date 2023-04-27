#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - function that builtin command that either
 *                 prints all aliases, specific
 *                 aliases, or sets an alias
 *
 * @args: array of arguments
 * @front: double pointer to the beginning of args
 *
 * Return: 0 (success) -1 (failure)
 */

int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tmp = aliases;
	int i, ret;
	char *val;

	ret = 0;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		val = _strchr(args[i], '=');
		if (!val)
		{
			while (tmp)
			{
				if (_strcmp(args[i], tmp->name) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				ret = create_error(args + i, 1);
		}
		else
			set_alias(args[i], val);
	}
	return (ret);
}

/**
 * set_alias - function that either set an existing alias 'name'
 *             with a new value,'value' or creates a new
 *             alias with 'name' and 'value'
 * @var_name: name of the alias
 * @value: value of the alias
 */

void set_alias(char *var_name, char *value)
{
	alias_t *tmp = aliases;
	int length, i, j;
	char *new_val;

	*value = '\0';
	value++;

	length = _strlen(value) - _strspn(value, "'\"");
	new_val = malloc(sizeof(char) * (length + 1));

	if (!new_val)
		return;

	for (i = 0, j = 0; value[i]; i++)
	{
		if (value[i] != '\'' && value[i] != '"')
			new_val[j++] = value[i];
	}
	new_val[j] = '\0';

	while (tmp)
	{
		if (_strcmp(var_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_val;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_alias_end(&aliases, var_name, new_val);
}

/**
 * print_alias - function that prints the alias in the format name = 'value'
 *
 * @alias: a pointer to an alias
 */

void print_alias(alias_t *alias)
{
	char *alias_string;
	int length = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (length + 1));

	if (!alias_string)
		return;

	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, length);
	free(alias_string);
}

/**
 * replace_aliases - function that goes through the arguments
 *                   and replace any matching alias with their value
 *
 * @args: A 2D pointer to the arguments
 *
 * Return: A 2D pointer to the arguments
 */

char **replace_aliases(char **args)
{
	alias_t *tmp;
	int i;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
		return (args);

	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(args[i], tmp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (!new_val)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_val, tmp->value);
				free(args[i]);
				args[i] = new_val;
				i--;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (args);
}
