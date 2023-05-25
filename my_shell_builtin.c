#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int check_exit;

	if (info->argv[1])  /* If there is an exit argument */
	{
		check_exit = ErrCheckAtoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			_putsError(info, "Illegal number: ");
			_iputs(info->argv[1]);
			_iputchar('\n');
			return (1);
		}
		info->err_num = ErrCheckAtoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * changeDir - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int changeDir(info_t *info)
{
	char *j, *dir, buffer[1024];
	int chdir_result;

	j = getcwd(buffer, 1024);
	if (!j)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = envGet(info, "HOME=");
		if (!dir)
			chdir_result = /* TODO: what should this be? */
				chdir((dir = envGet(info, "PWD=")) ? dir : "/");
		else
			chdir_result = chdir(dir);
	}
	else if (_comparestr(info->argv[1], "-") == 0)
	{
		if (!envGet(info, "OLDPWD="))
		{
			_puts(j);
			_putchar('\n');
			return (1);
		}
		_puts(envGet(info, "OLDPWD=")), _putchar('\n');
		chdir_result = /* TODO: what should this be? */
			chdir((dir = envGet(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		_putsError(info, "can't cd to ");
		_iputs(info->argv[1]), _iputchar('\n');
	}
	else
	{
		envSet(info, "OLDPWD", envGet(info, "PWD="));
		envSet(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_help(info_t *info)
{
	char **str_array;

	str_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*str_array); /* temp att_unused workaround */
	return (0);
}

