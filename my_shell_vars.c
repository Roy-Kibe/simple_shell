#include "shell.h"

/**
 * is_chain_delimiter - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buff, size_t *ptr)
{
	size_t k = *ptr;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buff[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[k] == '&' && buff[k + 1] == '&')
	{
		buff[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[k] == ';') /* found end of this command */
	{
		buff[k] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = k;
	return (1);
}

/**
 * _checkchainstatus - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @init: starting position in buf
 * @buf_len: length of buf
 *
 * Return: Void
 */
void _checkchainstatus(info_t *info, char *buff, size_t *ptr,
size_t init, size_t buf_len)
{
	size_t k = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[init] = 0;
			k = buf_len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[init] = 0;
			k = buf_len;
		}
	}

	*ptr = k;
}

/**
 * change_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_alias(info_t *info)
{
	int j;
	list_t *node;
	char *ptr;

	for (j = 0; j < 10; j++)
	{
		node = node_begins_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _chrstr(node->str, '=');
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
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] != '$' || !info->argv[n][1])
			continue;

		if (!_comparestr(info->argv[n], "$?"))
		{
			change_string(&(info->argv[n]),
				str_clone(convertNum(info->status, 10, 0)));
			continue;
		}
		if (!_comparestr(info->argv[n], "$$"))
		{
			change_string(&(info->argv[n]),
				str_clone(convertNum(getpid(), 10, 0)));
			continue;
		}
		node = node_begins_with(info->env, &info->argv[n][1], '=');
		if (node)
		{
			change_string(&(info->argv[n]),
				str_clone(_chrstr(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[n], str_clone(""));

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
