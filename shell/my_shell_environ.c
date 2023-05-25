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
	list_t *nod_s = info->env;
	char *t;

	while (nod_s)
	{
		t = begins_with(nod_s->str, env_name);
		if (t && *t)
			return (t);
		nod_s = nod_s->next;
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
		_iputs("Incorrect number of arguements\n");
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
	int a;

	if (info->argc == 1)
	{
		_iputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		envUnset(info, info->argv[a]);

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
	list_t *nod_s = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		appendNode(&nod_s, environ[a], 0);
	info->env = nod_s;
	return (0);
}
