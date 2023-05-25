#include "shell.h"

/**
 *_iputs - prints an input string
 * @strn: the string to be printed
 *
 * Return: Nothing
 */
void _iputs(char *strn)
{
	int i = 0;

	if (!strn)
		return;
	while (strn[i] != '\0')
	{
		_iputchar(strn[i]);
		i++;
	}
}

/**
 * _iputchar - writes the character c to stderr
 * @a: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _iputchar(char a)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (a != BUF_FLUSH)
		buf[j++] = a;
	return (1);
}

/**
 * _writefd - writes the character c to given fd
 * a: The character to print
 * @fileDescriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _writefd(char a, int fileDescriptor)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fileDescriptor, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 *_printsfd - prints an input string
 * @strn: the string to be printed
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int _printsfd(char *strn, int fileDescriptor)
{
	int i = 0;

	if (!strn)
		return (0);
	while (*strn)
	{
		i += _writefd(*strn++, fileDescriptor);
	}
	return (i);
}

