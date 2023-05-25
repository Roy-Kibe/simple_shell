#include "shell.h"

/**
 * _interactmode - a function that returns true if shell is in interactive mode
 * @info: the struct address
 *
 * Return: 1 if in interactive mode, otherwise return 0
 */
int _interactmode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - checks if character is a delimiter
 * @i: the char to check
 * @de_lim: the delimiter string
 * Return: 1 if true, otherwise return 0
 */
int isDelimiter(char i, char *de_lim)
{
	while (*de_lim)
		if (*de_lim++ == i)
			return (1);
	return (0);
}

/**
 *isAlphabet - checks if a character is an alphabet
 *@i: The character to be input
 *Return: 1 if i is an alphabet,otherwise return 0
 */

int isAlphabet(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *atoi_ - converts a string to an integer
 *@strn: the string to be converted
 *Return: 0 if no numbers in string, otherwise return converted number
 */

int atoi_(char *strn)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  strn[i] != '\0' && flag != 2; i++)
	{
		if (strn[i] == '-')
			sign *= -1;

		if (strn[i] >= '0' && strn[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (strn[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

