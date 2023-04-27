#include "shell.h"

int cant_open(char *file_path);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - function that prints can't open error if the
 *             file doesn't exist or lacks proper permissions
 *
 * @file_path: the path to the supposed file
 *
 * Return: 127
 */

int cant_open(char *file_path)
{
	char *error, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (127);

	length = _strlen(name) + _strlen(history_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (length + 1));

	if (!error)
	{
		free(history_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(history_str);
	write(STDERR_FILENO, error, length);
	free(error);
	return (127);
}

/**
 * proc_file_commands - function that takes a file and attempts to run the commands stored within
 * @file_path: path to the file
 * @exe_ret: the return value of the last executed command
 *
 * Return: 127 if file couldn't be opened
 *         -1 if malloc fails
 *         else the return value of the last command ran.
 */

int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t i, b_read, file;
	unsigned int line_size = 0;
	unsigned int init_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * init_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, init_size, line_size);
		_strcat(line, buffer);
		init_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
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

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * token_len - function that locates the delimiter index marking
 *             the end of the first token contained within a string
 *
 * @str: string to be searched
 * @delim: the delimiter character
 *
 * Return: the delimiter index
 */

int token_len(char *str, char *delim)
{
	int i, length;

	i = length = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		length++;
		i++;
	}
	return (length);
}

/**
 * count_tokens - function that counts the number of delimited words contained within a string
 *
 * @str: the string to be searched
 * @delim: the delimiter character
 *
 * Return: the number of words contained within str
 */

int count_tokens(char *str, char *delim)
{
	int i, length, token;

	length = token = 0;

	for (i = 0; *(str + i); i++)
		length++;

	for (i = 0; i < length; i++)
	{
		if (*(str + i) != *delim)
		{
			token++;
			i += token_len(str + i, delim);
		}
	}
	return (token);
}

/**
 * _strtok - function that tokenizes a string
 *
 * @line: the string ti be tokenized
 * @delim: delimiter character used to tokenize the string
 *
 * Return: pointer to an array containing the tokenized words
 */

char **_strtok(char *line, char *delim)
{
	char **ptr;
	int i, j, k, token, words;

	i = 0;

	token = count_tokens(line, delim);
	if (token == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (token + 2));
	if (!ptr)
		return (NULL);

	for (j = 0; j < token; j++)
	{
		while (line[i] == *delim)
			i++;

		words = token_len(line + i, delim);

		ptr[j] = malloc(sizeof(char) * (words + 1));
		if (!ptr[j])
		{
			for (i = i - 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}

		for (k = 0; k < words; k++)
		{
			ptr[j][k] = line[i];
			i++;
		}
		ptr[j][k] = '\0';
	}
	ptr[j] = NULL;
	ptr[j + 1] = NULL;

	return (ptr);
}
