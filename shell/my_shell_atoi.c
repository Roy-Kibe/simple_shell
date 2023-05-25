#include "shell.h"

/**
 * _interactmode - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int _interactmode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - checks if character is a delimeter
 * @i: the char to check
 * @de_lim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char i, char *de_lim)
{
	while (*de_lim)
		if (*de_lim++ == i)
			return (1);
	return (0);
}

/**
 *isAlphabet - checks for alphabetic character
 *@b: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
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
 *Return: 0 if no numbers in string, converted number otherwise
 */

int atoi_(char *strn)
{
	int a, sn = 1, flag = 0, output;
	unsigned int rslt = 0;

	for (a = 0;  strn[a] != '\0' && flag != 2; a++)
	{
		if (strn[a] == '-')
			sn *= -1;

		if (strn[a] >= '0' && strn[a] <= '9')
		{
			flag = 1;
			rslt *= 10;
			rslt += (strn[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sn == -1)
		output = -rslt;
	else
		output = rslt;

	return (output);
}
