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
	int a = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[a])
	{
		destination[a] = source[a];
		a++;
	}
	destination[a] = 0;
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
	int l = 0;
	char *rt;

	if (strn == NULL)
		return (NULL);
	while (*strn++)
		l++;
	rt = malloc(sizeof(char) * (l + 1));
	if (!rt)
		return (NULL);
	for (l++; l--;)
		rt[l] = *--strn;
	return (rt);
}

/**
 *_puts - prints an input string
 *@strn: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strn)
{
	int z = 0;

	if (!strn)
		return;
	while (strn[z] != '\0')
	{
		_putchar(strn[z]);
		z++;
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
	static int z;
	static char b[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(1, b, z);
		z = 0;
	}
	if (a != BUF_FLUSH)
		b[z++] = a;
	return (1);
}
