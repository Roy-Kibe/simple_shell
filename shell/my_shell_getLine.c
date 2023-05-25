#include "shell.h"

/**
 * inputBuffer - buffers chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t inputBuffer(info_t *info, char **buff, size_t *l)
{
	ssize_t a = 0;
	size_t l_p = 0;

	if (!*l) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buff, &l_p, stdin);
#else
		a = getLine(info, buff, &l_p);
#endif
		if (a > 0)
		{
			if ((*buff)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			info->linecount_flag = 1;
			filterComments(*buff);
			updateHistList(info, *buff, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*l = a;
				info->cmd_buf = buff;
			}
		}
	}
	return (a);
}

/**
 * readInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t readInput(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, b, l_s;
	ssize_t z = 0;
	char **buf_pr = &(info->arg), *pr;

	_putchar(BUF_FLUSH);
	z = inputBuffer(info, &buf, &l_s);
	if (z == -1) /* EOF */
		return (-1);
	if (l_s)	/* we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		pr = buf + a; /* get pointer for return */

		_checkchainstatus(info, buf, &b, a, l_s);
		while (b < l_s) /* iterate to semicolon or end */
		{
			if (is_chain_delimiter(info, buf, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= l_s) /* reached end of buffer? */
		{
			a = l_s = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_pr = pr; /* pass back pointer to current command position */
		return (_strlength(pr)); /* return length of current command */
	}

	*buf_pr = buf; /* else not a chain, pass back buffer from _getline() */
	return (z); /* return length of buffer from _getline() */
}

/**
 * readBuff - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @j: size
 *
 * Return: r
 */
ssize_t readBuff(info_t *info, char *buff, size_t *j)
{
	ssize_t z = 0;

	if (*j)
		return (0);
	z = read(info->readfd, buff, READ_BUF_SIZE);
	if (z >= 0)
		*j = z;
	return (z);
}

/**
 * getLine - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len_buff: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int getLine(info_t *info, char **ptr, size_t *len_buff)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, l_s;
	size_t b;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && len_buff)
		s = *len_buff;
	if (a == l_s)
		a = l_s = 0;

	r = readBuff(info, buf, &l_s);
	if (r == -1 || (r == 0 && l_s == 0))
		return (-1);

	c = _chrstr(buf + a, '\n');
	b = c ? 1 + (unsigned int)(c - buf) : l_s;
	new_p = realloc_mem(p, s, s ? s + b : b + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_catstrn(new_p, buf + a, b - a);
	else
		_cpystrn(new_p, buf + a, b - a + 1);

	s += b - a;
	a = b;
	p = new_p;

	if (len_buff)
		*len_buff = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
