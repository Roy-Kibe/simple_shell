#include "shell.h"

/**
 * inputBuffer - buffers chained commands
 * @f: parameter struct
 * @buff: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t inputBuffer(info_t *f, char **buff, size_t *l)
{
	ssize_t y = 0;
	size_t l_p = 0;

	if (!l) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)f->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		y = getline(buff, &l_p, stdin);
#else
		y = getLine(f, buff, &l_p);
#endif
		if (y > 0)
		{
			if ((*buff)[y - 1] == '\n')
			{
				(buff)[y - 1] = '\0'; /* remove trailing newline */
				y--;
			}
			f->linecount_flag = 1;
			filterComments(*buff);
			updateHistList(f, *buff, f->histcount++);
			/* if (_chrstr(*buff, ';')) is this a command chain? */
			{
				*l = y;
				f->cmd_buf = buff;
			}
		}
	}
	return (y);
}

/**
 * readInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t readInput(info_t *info)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t m, n, size;
	ssize_t y = 0;
	char **buf_p = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	y = inputBuffer(info, &buff, &size);
	if (y == -1) /* EOF */
		return (-1);
	if (size)	/* we have commands left in the chain buffer */
	{
		n = m; /* init new iterator to current buff position */
		ptr = buff + m; /* get pointer for return */

		_checkchainstatus(info, buff, &n, m, size);
		while (n < size) /* iterate to semicolon or end */
		{
			if (is_chain_delimiter(info, buff, &n))
				break;
			n++;
		}

		m = n + 1; /* increment past nulled ';'' */
		if (m >= size) /* reached end of buffer? */
		{
			m = size = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr; /* pass back pointer to current command position */
		return (_strlength(ptr)); /* return length of current command */
	}

	*buf_p = buff; /* else not a chain, pass back buffer from getLine() */
	return (y); /* return length of buffer from getLine() */
}

/**
 * readBuff - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @j: size
 *
 * Return: y
 */
ssize_t readBuff(info_t *info, char *buff, size_t *j)
{
	ssize_t y = 0;

	if (*j)
		return (0);
	y = read(info->readfd, buff, READ_BUF_SIZE);
	if (y >= 0)
		*j = y;
	return (y);
}

/**
 * getLine - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len_buff: size of preallocated ptr buffer if not NULL
 *
 * Return: t
 */
int getLine(info_t *info, char **ptr, size_t *len_buff)
{
	static char buff[READ_BUF_SIZE];
	static size_t j, size;
	size_t l;
	ssize_t y = 0, t = 0;
	char *p = NULL, *new_ptr = NULL, *a;

	p = *ptr;
	if (p && len_buff)
		t = *len_buff;
	if (j == size)
		j = size = 0;

	y = readBuff(info, buff, &size);
	if (y == -1 || (y == 0 && size == 0))
		return (-1);

	a = _chrstr(buff + j, '\n');
	l = a ? 1 + (unsigned int)(a - buff) : size;
	new_ptr = realloc_mem(p, t, t ? t + l : l + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (t)
		_catstrn(new_ptr, buff + j, l - j);
	else
		_cpystrn(new_ptr, buff + j, l - j + 1);

	t += l - j;
	j = l;
	p = new_ptr;

	if (len_buff)
		*len_buff = t;
	*ptr = p;
	return (t);
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
