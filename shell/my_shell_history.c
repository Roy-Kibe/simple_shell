#include "shell.h"

/**
 * FetchHistFile - gets the history file
 * @argInfo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *FetchHistFile(info_t *argInfo)
{
	char *buff, *dr;

	dr = envGet(argInfo, "HOME=");
	if (!dr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlength(dr) + _strlength(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	cpy_str(buff, dr);
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
	ssize_t f_d;
	char *file_name = FetchHistFile(argInfo);
	list_t *nod_s = NULL;

	if (!file_name)
		return (-1);

	f_d = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (f_d == -1)
		return (-1);
	for (nod_s = argInfo->history; nod_s; nod_s = nod_s->next)
	{
		_printsfd(nod_s->str, f_d);
		_writefd('\n', f_d);
	}
	_writefd(BUF_FLUSH, f_d);
	close(f_d);
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
	int a, lt = 0, line_count = 0;
	ssize_t f_d, rd_len, f_size = 0;
	struct stat st;
	char *buf = NULL, *file_name =  FetchHistFile(argInfo);

	if (!file_name)
		return (0);

	f_d = open(file_name, O_RDONLY);
	free(file_name);
	if (f_d == -1)
		return (0);
	if (!fstat(f_d, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (f_size + 1));
	if (!buf)
		return (0);
	rd_len = read(f_d, buf, f_size);
	buf[f_size] = 0;
	if (rd_len <= 0)
		return (free(buf), 0);
	close(f_d);
	for (a = 0; a < f_size; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			updateHistList(argInfo, buf + lt, line_count++);
			lt = a + 1;
		}
	if (lt != a)
		updateHistList(argInfo, buf + lt, line_count++);
	free(buf);
	argInfo->histcount = line_count;
	while (argInfo->histcount-- >= HIST_MAX)
		remove_node_at_index(&(argInfo->history), 0);
	reindexHist(argInfo);
	return (argInfo->histcount);
}

/**
 * updateHistList - adds entry to a history linked list
 * @argInfo: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @line_count: the history linecount, histcount
 *
 * Return: Always 0
 */
int updateHistList(info_t *argInfo, char *buff, int line_count)
{
	list_t *nod_s = NULL;

	if (argInfo->history)
		nod_s = argInfo->history;
	appendNode(&nod_s, buff, line_count);

	if (!argInfo->history)
		argInfo->history = nod_s;
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
	list_t *nod_s = argInfo->history;
	int a = 0;

	while (nod_s)
	{
		nod_s->num = a++;
		nod_s = nod_s->next;
	}
	return (argInfo->histcount = a);
}

