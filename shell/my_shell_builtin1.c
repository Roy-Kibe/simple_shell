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
	char *a, d;
	int rtn;

	a = _chrstr(strn, '=');
	if (!a)
		return (1);
	d = *a;
	*a = 0;
	rtn = remove_node_at_index(&(info->alias),
		locate_node_index(info->alias, node_begins_with(info->alias, strn, -1)));
	*a = d;
	return (rtn);
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
	char *t;

	t = _chrstr(strn, '=');
	if (!t)
		return (1);
	if (!*++t)
		return (aliasUnset(info, strn));

	aliasUnset(info, strn);
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
	char *z = NULL, *b = NULL;

	if (alias_node)
	{
		z = _chrstr(alias_node->str, '=');
		for (b = alias_node->str; b <= z; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(z + 1);
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
	int a = 0;
	char *t = NULL;
	list_t *nod = NULL;

	if (info->argc == 1)
	{
		nod = info->alias;
		while (nod)
		{
			aliasPrint(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		t = _chrstr(info->argv[a], '=');
		if (t)
			aliasSet(info, info->argv[a]);
		else
			aliasPrint(node_begins_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
