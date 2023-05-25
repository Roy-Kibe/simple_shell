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
	list_t *nod_s = info->env;
	size_t a = 0;
	char *t;

	if (!nod_s || !env_var)
		return (0);

	while (nod_s)
	{
		t = begins_with(nod_s->str, env_var);
		if (t && *t == '=')
		{
			info->env_changed = remove_node_at_index(&(info->env), a);
			a = 0;
			nod_s = info->env;
			continue;
		}
		nod_s = nod_s->next;
		a++;
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
	char *bu = NULL;
	list_t *nod_s;
	char *t;

	if (!strvar || !str_value)
		return (0);

	bu = malloc(_strlength(strvar) + _strlength(str_value) + 2);
	if (!bu)
		return (1);
	cpy_str(bu, strvar);
	cat_str(bu, "=");
	cat_str(bu, str_value);
	nod_s = info->env;
	while (nod_s)
	{
		t = begins_with(nod_s->str, strvar);
		if (t && *t == '=')
		{
			free(nod_s->str);
			nod_s->str = bu;
			info->env_changed = 1;
			return (0);
		}
		nod_s = nod_s->next;
	}
	appendNode(&(info->env), bu, 0);
	free(bu);
	info->env_changed = 1;
	return (0);
}

