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
	int ai, bj;
	char *st = strdest;

	ai = 0;
	while (strsrc[ai] != '\0' && ai < num - 1)
	{
		strdest[ai] = strsrc[ai];
		ai++;
	}
	if (ai < num)
	{
		bj = ai;
		while (bj < num)
		{
			strdest[bj] = '\0';
			bj++;
		}
	}
	return (st);
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
	int ai, bj;
	char *st = strdest;

	ai = 0;
	bj = 0;
	while (strdest[ai] != '\0')
		ai++;
	while (strsrc[bj] != '\0' && bj < num)
	{
		strdest[ai] = strsrc[bj];
		ai++;
		bj++;
	}
	if (bj < num)
		strdest[ai] = '\0';
	return (st);
}

/**
 **_chrstr - locates a character in a string
 *@strn: the string to be parsed
 *@a: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_chrstr(char *strn, char a)
{
	do {
		if (*strn == a)
			return (strn);
	} while (*strn++ != '\0');

	return (NULL);
}

