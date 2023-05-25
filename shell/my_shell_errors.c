#include "shell.h"

/**
 *_iputs - prints an input string
 * @strn: the string to be printed
 *
 * Return: Nothing
 */
void _iputs(char *strn)
{
	int b = 0;

	if (!strn)
		return;
	while (strn[b] != '\0')
	{
		_iputchar(strn[b]);
		b++;
	}
}

/**
 * _iputchar - writes the character c to stderr
 * @b: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _iputchar(char b)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (b != BUF_FLUSH)
		buff[a++] = b;
	return (1);
}

/**
 * _writefd - writes the character c to given fd
 * @a: The character to print
 * @fileDescriptor: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _writefd(char a, int fileDescriptor)
{
	static int b;
	static char buff[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(fileDescriptor, buff, b);
		b = 0;
	}
	if (a != BUF_FLUSH)
		buff[b++] = a;
	return (1);
}

/**
 *_printsfd - prints an input string
 * @strn: the string to be printed
 * @fileDescriptor: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _printsfd(char *strn, int fileDescriptor)
{
	int z = 0;

	if (!strn)
		return (0);
	while (*strn)
	{
		z += _writefd(*strn++, fileDescriptor);
	}
	return (z);
}
