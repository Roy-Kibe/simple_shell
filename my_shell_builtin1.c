#include "shell.h"

/**
 * historyData - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int historyData(info_t *info)
{
	display_list(info->history);
	return (0);
}

/**
 * aliasUnset - sets alias to string
 * @info: parameter struct
 * @strn: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int aliasUnset(info_t *info, char *strn)
{
	char *p, j;
	int result;

	p = _chrstr(strn, '=');
	if (!p)
		return (1);
	j = *p;
	*p = 0;
	result = remove_node_at_index(&(info->alias),
		locate_node_index(info->alias, node_begins_with(info->alias, strn, -1)));
	*p = j;
	return (result);
}

/**
 * aliasSet - sets alias to string
 * @info: parameter struct
 * @strn: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int aliasSet(info_t *info, char *strn)
{
	char *p;

	p = _chrstr(strn, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (aliasSet(info, strn));

	aliasSet(info, strn);
	return (appendNode(&(info->alias), strn, 0) == NULL);
}

/**
 * aliasPrint - prints an alias string
 * @alias_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int aliasPrint(list_t *alias_node)
{
	char *p = NULL, *a = NULL;

	if (alias_node)
	{
		p = _chrstr(alias_node->str, '=');
		for (a = alias_node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myAlias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myAlias(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			aliasPrint(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = _chrstr(info->argv[j], '=');
		if (p)
			aliasSet(info, info->argv[j]);
		else
			aliasPrint(node_begins_with(info->alias, info->argv[j], '='));
	}

	return (0);
}

