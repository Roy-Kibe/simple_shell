#include "shell.h"

/**
 **_cpystrn - copies a string
 *@strdest: the destination string to be copied to
 *@strsrc: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_cpystrn(char *strdest, char *strsrc, int num)
{
	int m, n;
	char *s = strdest;

	m = 0;
	while (strsrc[m] != '\0' && m < num - 1)
	{
		strdest[m] = strsrc[m];
		m++;
	}
	if (m < num)
	{
		n = m;
		while (n < num)
		{
			strdest[n] = '\0';
			n++;
		}
	}
	return (s);
}

/**
 **_catstrn - concatenates two strings
 *@strdest: the first string
 *@strsrc: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_catstrn(char *strdest, char *strsrc, int num)
{
	int m, n;
	char *s = strdest;

	m = 0;
	n = 0;
	while (strdest[m] != '\0')
		m++;
	while (strsrc[n] != '\0' && n < num)
	{
		strdest[m] = strsrc[n];
		m++;
		n++;
	}
	if (n < num)
		strdest[m] = '\0';
	return (s);
}

/**
 **_chrstr - locates a character in a string
 *@strn: the string to be parsed
 *@a: the character to look for
 *Return: (strn) a pointer to the memory area strn
 */
char *_chrstr(char *strn, char a)
{
	do {
		if (*strn == a)
			return (strn);
	} while (*strn++ != '\0');

	return (NULL);
}

