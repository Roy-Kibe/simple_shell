#include "shell.h"

/**
 * cpy_str - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *cpy_str(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}

/**
 * str_clone - duplicates a string
 * @strn: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *str_clone(const char *strn)
{
	int len = 0;
	char *result;

	if (strn == NULL)
		return (NULL);
	while (*strn++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--strn;
	return (result);
}

/**
 *_puts - prints an input string
 *@strn: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strn)
{
	int n = 0;

	if (!strn)
		return;
	while (strn[n] != '\0')
	{
		_putchar(strn[n]);
		n++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @a: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char a)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (a != BUF_FLUSH)
		buf[j++] = a;
	return (1);
}
