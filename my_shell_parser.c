#include "shell.h"


/**
 * cmd_check - determines if a file is an executable command
 * @info: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cmd_check(info_t *info, char *file_path)
{
	struct stat st;

	(void)info;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * clone_chars - duplicates characters
 * @str_path: the PATH string
 * @initial_index: starting index
 * @final_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *clone_chars(char *str_path, int initial_index, int final_index)
{
	static char buf[1024];
	int i = 0, n = 0;

	for (n = 0, i = initial_index; i < final_index; i++)
		if (str_path[i] != ':')
			buf[n++] = str_path[i];
	buf[n] = 0;
	return (buf);
}

/**
 * get_path - finds this cmd in the PATH string
 * @info: the info struct
 * @str_path: the PATH string
 * @cmd_file: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *get_path(info_t *info, char *str_path, char *cmd_file)
{
	int i = 0, current_pos = 0;
	char *file_path;

	if (!str_path)
		return (NULL);
	if ((_strlength(cmd_file) > 2) && begins_with(cmd_file, "./"))
	{
		if (cmd_check(info, cmd_file))
			return (cmd_file);
	}
	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			file_path = clone_chars(str_path, current_pos, i);
			if (!*file_path)
				cat_str(file_path, cmd_file);
			else
			{
				cat_str(file_path, "/");
			    cat_str(file_path, cmd_file);
			}
			if (cmd_check(info, file_path))
				return (file_path);
			if (!str_path[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}
