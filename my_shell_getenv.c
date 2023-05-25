#include "shell.h"

/**
 * getEnviron - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getEnviron(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_text(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * envUnset - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @env_var: the string env var property
 */
int envUnset(info_t *info, char *env_var)
{
	list_t *alias_node = info->env;
	size_t i = 0;
	char *ptr;

	if (!alias_node || !env_var)
		return (0);

	while (alias_node)
	{
		ptr = begins_with(alias_node->str, env_var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = remove_node_at_index(&(info->env), i);
			i = 0;
			alias_node = info->env;
			continue;
		}
		alias_node = alias_node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * envSet - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @strvar: the string env var property
 * @str_value: the string env var value
 *  Return: Always 0
 */
int envSet(info_t *info, char *strvar, char *str_value)
{
	char *buf = NULL;
	list_t *alias_node;
	char *ptr;

	if (!strvar || !str_value)
		return (0);

	buf = malloc(_strlength(strvar) + _strlength(str_value) + 2);
	if (!buf)
		return (1);
	cpy_str(buf, strvar);
	cat_str(buf, "=");
	cat_str(buf, str_value);
	alias_node = info->env;
	while (alias_node)
	{
		ptr = begins_with(alias_node->str, strvar);
		if (ptr && *ptr == '=')
		{
			free(alias_node->str);
			alias_node->str = buf;
		info->env_changed = 1;
			return (0);
		}
		alias_node = alias_node->next;
	}
	appendNode(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

