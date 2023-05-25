#include "shell.h"

/**
 * envPrint - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int envPrint(info_t *info)
{
	DisplayStrList(info->env);
	return (0);
}

/**
 * envGet - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @env_name: env var name
 *
 * Return: the value
 */
char *envGet(info_t *info, const char *env_name)
{
	list_t *alias_node = info->env;
	char *p;

	while (alias_node)
	{
		p = begins_with(alias_node->str, env_name);
		if (p && *p)
			return (p);
		alias_node = alias_node->next;
	}
	return (NULL);
}

/**
 * setEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int setEnv(info_t *info)
{
	if (info->argc != 3)
	{
		_iputs("Incorrect number of arguments\n");
		return (1);
	}
	if (envSet(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unsetEnv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_iputs("Too few arguments.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		envUnset(info, info->argv[j]);

	return (0);
}

/**
 * FillEnvData - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int FillEnvData(info_t *info)
{
	list_t *alias_node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		appendNode(&alias_node, environ[j], 0);
	info->env = alias_node;
	return (0);
}

