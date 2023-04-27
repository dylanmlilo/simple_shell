#include "shell.h"

char *_strchr(char *str, char c);
int _strspn(char *str, char *accept);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);

/**
 * _strchr - function that locates a character in a string
 *
 * @str: string to be searched
 * @c: character to be located
 *
 * Return: A pointer to the first occurence if c is found
 *         else NULL if c is not found
 */

char *_strchr(char *str, char c)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == c)
			return (str + i);
	}
	return (NULL);
}

/**
 * _strspn - functon that gets the length of a prefix substring
 *
 * @str: the string to be searched
 * @accept: prefix to be measured
 *
 * Return: number of bytes in s which
 *         consist only of bytes from accept
 */

int _strspn(char *str, char *accept)
{
	int bytes;
	int i;

	bytes = 0;

	while (*str)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*str == accept[i])
			{
				bytes++;
				break;
			}
		}
		str++;
	}
	return (bytes);
}

/**
 * _strcmp - function that Compares two strings
 *
 * @str1: the first string to be compared
 * @str2: the second string to be compared
 *
 * Return: Positive byte difference if str1 > str2
 *         0 if str1 == str2
 *         Negative byte difference if str1 < str2
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - function that compare two strings
 *
 * @str1: pointer to a string
 * @str2: pointer to a string
 * @n: the first n bytes of the strings to compare
 *
 * Return: Negative than 0 if str1 is shorter than str2
 *         0 if str1 == str2
 *         Positive 0 if str1 is longer than str2
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t size;

	for (size = 0; str1[size] && str2[size] && size < n; size++)
	{
		if (str1[size] > str2[size])
			return (str1[size] - str2[size]);
		else if (str1[size] < str2[size])
			return (str1[size] - str2[size]);
	}
	if (size == n)
		return (0);
	else
		return (-10);
}
