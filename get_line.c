#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - function that reallocates a memory block using malloc and free
 *
 * @ptr: pointer to the memory previously allocated
 * @old_size: size in bytes of the allocated space for ptr
 * @new_size: size in bytes for the new memory block
 *
 * Return: ptr if new_size == old_size
 *         NULL if new_size == 0 and ptr is != NULL
 *         else a pointer to the reallocated memory block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *memory;
	char *ptr_copy, *fill;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		memory = malloc(new_size);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	memory = malloc(sizeof(*ptr_copy) * new_size);
	if (memory == NULL)
	{
		free(ptr);
		return (NULL);
	}

	fill = memory;

	for (i = 0; i < old_size && i < new_size; i++)
		fill[i] = *ptr_copy++;

	free(ptr);
	return (memory);
}

/**
 * assign_lineptr -function that reassigns the lineptr variable for _getline
 *
 * @lineptr: buffer to store an input string
 * @buffer: The string to assign to lineptr
 * @n: The size of lineptr
 * @b: The size of buffer
 *
 * Return: Nothing
 */

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - function that reads input from a stream
 *
 * @lineptr: a buffer to store the input
 * @n: the size of lineptr
 * @stream: the stream to read from
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t code;
	ssize_t ret;
	char c = 'c', *buffer;
	int _read;

	if (code == 0)
		fflush(stream);
	else
		return (-1);
	code = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		_read = read(STDIN_FILENO, &c, 1);
		if (_read == -1 || (_read == 0 && code == 0))
		{
			free(buffer);
			return (-1);
		}
		if (_read == 0 && code != 0)
		{
			code++;
			break;
		}
		if (code >= 120)
			buffer = _realloc(buffer, code, code + 1);

		buffer[code] = c;
		code++;
	}
	buffer[code] = '\0';

	assign_lineptr(lineptr, n, buffer, code);

	ret = code;
	if (_read != 0)
		code = 0;
	return (ret);
}
