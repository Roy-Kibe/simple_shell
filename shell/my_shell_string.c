#include "shell.h"

/**
 * _strlength - returns the length of a string
 * @st: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlength(char *st)
{
	int z = 0;

	if (!st)
		return (0);

	while (*st++)
		z++;
	return (z);
}

/**
 * _comparestr - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _comparestr(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * begins_with - checks if needle starts with haystack
 * @haystk: string to search
 * @ndl: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *begins_with(const char *haystk, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *haystk++)
			return (NULL);
	return ((char *)haystk);
}

/**
 * cat_str - concatenates two strings
 * @buf_dest: the destination buffer
 * @buf_src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *cat_str(char *buf_dest, char *buf_src)
{
	char *rt = buf_dest;

	while (*buf_dest)
		buf_dest++;
	while (*buf_src)
		*buf_dest++ = *buf_src++;
	*buf_dest = *buf_src;
	return (rt);
}
