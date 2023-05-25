#include "shell.h"

/**
 * ErrCheckAtoi - converts a string to an integer
 * @strn: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int ErrCheckAtoi(char *strn)
{
	int i = 0;
	unsigned long int result = 0;

	if (*strn == '+')
		strn++;  /* TODO: why does this make main return 255? */
	for (i = 0;  strn[i] != '\0'; i++)
	{
		if (strn[i] >= '0' && strn[i] <= '9')
		{
			result *= 10;
			result += (strn[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _putsError - prints an error message
 * @argInfo: the parameter & return info struct
 * @estrn: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void _putsError(info_t *argInfo, char *estrn)
{
	_iputs(argInfo->fname);
	_iputs(": ");
	print_decimal(argInfo->line_count, STDERR_FILENO);
	_iputs(": ");
	_iputs(argInfo->argv[0]);
	_iputs(": ");
	_iputs(estrn);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @userInput: the input
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int userInput, int fileDescriptor)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fileDescriptor == STDERR_FILENO)
		__putchar = _iputchar;
	if (userInput < 0)
	{
		_abs_ = -userInput;
		__putchar('-');
		count++;
	}
	else
		_abs_ = userInput;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertNum - converter function, a clone of itoa
 * @digit: number
 * @baseNum: base
 * @argFlags: argument flags
 *
 * Return: string
 */
char *convertNum(long int digit, int baseNum, int argFlags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = digit;

	if (!(argFlags & CONVERT_UNSIGNED) && digit < 0)
	{
		n = -digit;
		sign = '-';

	}
	arr = argFlags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = arr[n % baseNum];
		n /= baseNum;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * filterComments - function replaces first instance of '#' with '\0'
 * @strbuf: address of the string to modify
 *
 * Return: Always 0;
 */
void filterComments(char *strbuf)
{
	int i;

	for (i = 0; strbuf[i] != '\0'; i++)
		if (strbuf[i] == '#' && (!i || strbuf[i - 1] == ' '))
		{
			strbuf[i] = '\0';
			break;
		}
}

