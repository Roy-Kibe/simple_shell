#include "shell.h"

/**
 * infoReset - initializes info_t struct
 * @info: struct address
 */
void infoReset(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * infoSet - initializes info_t struct
 * @info: struct address
 * @argvect: argument vector
 */
void infoSet(info_t *info, char **argvect)
{
	int a = 0;

	info->fname = argvect[0];
	if (info->arg)
	{
		info->argv = str_split(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_clone(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		change_alias(info);
		change_vars(info);
	}
}

/**
 * infoFree - frees info_t struct fields
 * @info: struct address
 * @all_fields: true if freeing all fields
 */
void infoFree(info_t *info, int all_fields)
{
	free_string_set(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all_fields)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			clear_list(&(info->env));
		if (info->history)
			clear_list(&(info->history));
		if (info->alias)
			clear_list(&(info->alias));
		free_string_set(info->environ);
			info->environ = NULL;
		_freeptr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

