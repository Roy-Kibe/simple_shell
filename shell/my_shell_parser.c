#include "shell.h"

/**
 * cmd_check - determines if a file is an executable command
 * @f: the info struct
 * @pth: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cmd_check(info_t *f, char *pth)
{
	struct stat st;

	(void)f;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * clone_chars - duplicates characters
 * @path_str: the PATH string
 * @nw: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer
 */
char *clone_chars(char *path_str, int nw, int end)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = nw; a < end; a++)
		if (path_str[a] != ':')
			buf[b++] = path_str[a];
	buf[b] = 0;
	return (buf);
}

/**
 * get_path - finds this cmd in the PATH string
 * @f: the info struct
 * @path_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *get_path(info_t *f, char *path_str, char *cmd)
{
	int a = 0, curr_p = 0;
	char *p;

	if (!path_str)
		return (NULL);
	if ((_strlength(cmd) > 2) && begins_with(cmd, "./"))
	{
		if (cmd_check(f, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[a] || path_str[a] == ':')
		{
			p = clone_chars(path_str, curr_p, a);
			if (!*p)
				cat_str(p, cmd);
			else
			{
				cat_str(p, "/");
				cat_str(p, cmd);
			}
			if (cmd_check(f, p))
				return (p);
			if (!path_str[a])
				break;
			curr_p = a;
		}
		a++;
	}
	return (NULL);
}
