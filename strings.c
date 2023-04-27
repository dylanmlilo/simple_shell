#include "shell.h"

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - functin that returns the length of a string
 *
 * @str: pointer to the characters string
 *
 * Return: the length of the character string
 */

int _strlen(const char *str)
{
	int length;

	length = 0;

	if (!str)
		return (length);

	for (length = 0; str[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - function that copies the string pointed to by src, including
 *           the terminating null byte, to the buffer pointed by des
 *
 * @dest: a pointer to the destination of copied string
 * @src: a pointer to the src of the source string
 *
 * Return: a pointer to dest
 */

char *_strcpy(char *dest, const char *src)
{
	size_t size;

	for (size = 0; src[size] != '\0'; size++)
		dest[size] = src[size];

	dest[size] = '\0';
	return (dest);
}

/**
 * _strcat - function that concantenates two strings
 *
 * @dest: a pointer to destination string
 * @src: a pointer to source string
 *
 * Return: a pointer to destination string
 */

char *_strcat(char *dest, const char *src)
{
	char *dest_temp;
	const char *src_temp;

	dest_temp = dest;
	src_temp =  src;

	while (*dest_temp != '\0')
		dest_temp++;

	while (*src_temp != '\0')
		*dest_temp++ = *src_temp++;

	*dest_temp = '\0';
	return (dest);
}

/**
 * _strncat - function that concantenates two strings where
 *            n number of bytes are copied from source
 *
 * @dest: a pointer to destination string
 * @src: a pointer to source string
 * @n: the n bytes to copy from src
 *
 * Return: a pointer to destination string
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_length = _strlen(dest);
	size_t size;

	for (size = 0; size < n && src[size] != '\0'; size++)
		dest[dest_length + size] = src[size];

	dest[dest_length + size] = '\0';

	return (dest);
}
