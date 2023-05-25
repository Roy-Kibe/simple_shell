#include "shell.h"

/**
 * FetchHistFile- gets the history file
 * @argInfo: parameter struct
 *
 * Return: allocated string containing history file
 */

char *FetchHistFile(info_t *argInfo)
{
	char *buff, *dir;

	dir = envGet(argInfo, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlength(dir) + _strlength(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	cpy_str(buff, dir);
	cat_str(buff, "/");
	cat_str(buff, HIST_FILE);
	return (buff);
}

/**
 * store_history - creates a file, or appends to an existing file
 * @argInfo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int store_history(info_t *argInfo)
{
	ssize_t fd;
	char *filename = FetchHistFile(argInfo);
	list_t *alias_node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (alias_node = argInfo->history; alias_node; alias_node = alias_node->next)
	{
		_printsfd(alias_node->str, fd);
		_writefd('\n', fd);
	}
	_writefd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * access_history - reads history from file
 * @argInfo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int access_history(info_t *argInfo)
{
	int j, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *fn = FetchHistFile(argInfo);

	if (!fn)
		return (0);

	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			updateHistList(argInfo, buff + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		updateHistList(argInfo, buff + last, linecount++);
	free(buff);
	argInfo->histcount = linecount;
	while (argInfo->histcount-- >= HIST_MAX)
		remove_node_at_index(&(argInfo->history), 0);
	reindexHist(argInfo);
	return (argInfo->histcount);
}

/**
 * updateHistList - adds entry to a history linked list
 * @argInfo: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int updateHistList(info_t *argInfo, char *buff, int linecount)
{
	list_t *alias_node = NULL;

	if (argInfo->history)
		alias_node = argInfo->history;
	appendNode(&alias_node, buff, linecount);

	if (!argInfo->history)
		argInfo->history = alias_node;
	return (0);
}

/**
 * reindexHist - renumbers the history linked list after changes
 * @argInfo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int reindexHist(info_t *argInfo)
{
	list_t *alias_node = argInfo->history;
	int j = 0;

	while (alias_node)
	{
		alias_node->num = j++;
		alias_node = alias_node->next;
	}
	return (argInfo->histcount = j);
}

