#include "shell.h"

/**
 * ErrCheckAtoi - converts a string to an integer
 * @strn: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int ErrCheckAtoi(char *strn)
{
	int a = 0;
	unsigned long int rslt = 0;

	if (*strn == '+')
		strn++;  /* TODO: why does this make main return 255? */
	for (a = 0;  strn[a] != '\0'; a++)
	{
		if (strn[a] >= '0' && strn[a] <= '9')
		{
			rslt *= 10;
			rslt += (strn[a] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
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
 * @fileDescriptor: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int userInput, int fileDescriptor)
{
	int (*__putchar)(char) = _putchar;
	int a, ct = 0;
	unsigned int _abs_, curr;

	if (fileDescriptor == STDERR_FILENO)
		__putchar = _iputchar;
	if (userInput < 0)
	{
		_abs_ = -userInput;
		__putchar('-');
		ct++;
	}
	else
		_abs_ = userInput;
	curr = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + curr / a);
			ct++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	ct++;

	return (ct);
}

/**
 * convertNum - converter function, a clone of itoa
 * @digit: number
 * @baseNum: base
 * @argflags: argument flags
 *
 * Return: string
 */
char *convertNum(long int digit, int baseNum, int argflags)
{
	static char *ar;
	static char buff[50];
	char sn = 0;
	char *pr;
	unsigned long a = digit;

	if (!(argflags & CONVERT_UNSIGNED) && digit < 0)
	{
		a = -digit;
		sn = '-';

	}
	ar = argflags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pr = &buff[49];
	*pr = '\0';

	do	{
		*--pr = ar[a % baseNum];
		a /= baseNum;
	} while (a != 0);

	if (sn)
		*--pr = sn;
	return (pr);
}

/**
 * filterComments - function replaces first instance of '#' with '\0'
 * @strbuf: address of the string to modify
 *
 * Return: Always 0;
 */
void filterComments(char *strbuf)
{
	int a;

	for (a = 0; strbuf[a] != '\0'; a++)
		if (strbuf[a] == '#' && (!a || strbuf[a - 1] == ' '))
		{
			strbuf[a] = '\0';
			break;
		}
}

