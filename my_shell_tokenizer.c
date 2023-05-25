#include "shell.h"

/**
 * **str_split - splits a string into words. Repeat delimiters are ignored
 * @strn: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_split(char *strn, char *d)
{
	int a, b, c, f, totalwords = 0;
	char **s;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; strn[a] != '\0'; a++)
		if (!isDelimiter(strn[a], d) &&
(isDelimiter(strn[a + 1], d) || !strn[a + 1]))
			totalwords++;

	if (totalwords == 0)
		return (NULL);
	s = malloc((1 + totalwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < totalwords; b++)
	{
		while (isDelimiter(strn[a], d))
			a++;
		c = 0;
		while (!isDelimiter(strn[a + c], d) && strn[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			s[b][f] = strn[a++];
		s[b][f] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **str_split2 - splits a string into words
 * @strn: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **str_split2(char *strn, char d)
{
	int a, b, c, f, totalwords = 0;
	char **s;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	for (a = 0; strn[a] != '\0'; a++)
		if ((strn[a] != d && strn[a + 1] == d) ||
		    (strn[a] != d && !strn[a + 1]) || strn[a + 1] == d)
			totalwords++;
	if (totalwords == 0)
		return (NULL);
	s = malloc((1 + totalwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < totalwords; b++)
	{
		while (strn[a] == d && strn[a] != d)
			a++;
		c = 0;
		while (strn[a + c] != d && strn[a + c] && strn[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			s[b][f] = strn[a++];
		s[b][f] = 0;
	}
	s[b] = NULL;
	return (s);
}
