#include "shell.h"

/**
 * is_chain_delimiter - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buff, size_t *ptr)
{
	size_t z = *ptr;

	if (buff[z] == '|' && buff[z + 1] == '|')
	{
		buff[z] = 0;
		z++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[z] == '&' && buff[z + 1] == '&')
	{
		buff[z] = 0;
		z++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[z] == ';') /* found end of this command */
	{
		buff[z] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = z;
	return (1);
}

/**
 * _checkchainstatus - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @in: starting position in buf
 * @buf_len: length of buf
 *
 * Return: Void
 */
void _checkchainstatus(info_t *info, char *buff, size_t *ptr,
		size_t in, size_t buf_len)
{
	size_t b = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[in] = 0;
			b = buf_len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[in] = 0;
			b = buf_len;
		}
	}

	*ptr = b;
}

/**
 * change_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_alias(info_t *info)
{
	int b;
	list_t *nod_s;
	char *ptr;

	for (b = 0; b < 10; b++)
	{
		nod_s = node_begins_with(info->alias, info->argv[0], '=');
		if (!nod_s)
			return (0);
		free(info->argv[0]);
		ptr = _chrstr(nod_s->str, '=');
		if (!ptr)
			return (0);
		ptr = str_clone(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * change_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_vars(info_t *info)
{
	int a = 0;
	list_t *nod_s;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_comparestr(info->argv[a], "$?"))
		{
			change_string(&(info->argv[a]),
				str_clone(convertNum(info->status, 10, 0)));
			continue;
		}
		if (!_comparestr(info->argv[a], "$$"))
		{
			change_string(&(info->argv[a]),
				str_clone(convertNum(getpid(), 10, 0)));
			continue;
		}
		nod_s = node_begins_with(info->env, &info->argv[a][1], '=');
		if (nod_s)
		{
			change_string(&(info->argv[a]),
				str_clone(_chrstr(nod_s->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[a], str_clone(""));

	}
	return (0);
}

/**
 * change_string - replaces string
 * @prev: address of old string
 * @updated: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_string(char **prev, char *updated)
{
	free(*prev);
	*prev = updated;
	return (1);
}
