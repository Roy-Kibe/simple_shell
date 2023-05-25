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
	int e_ch;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		e_ch = ErrCheckAtoi(info->argv[1]);
		if (e_ch == -1)
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
	char *st, *d, b[1024];
	int chd_ret;

	st = getcwd(b, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		d = envGet(info, "HOME=");
		if (!d)
			chd_ret = /* TODO: what should this be? */
				chdir((d = envGet(info, "PWD=")) ? d : "/");
		else
			chd_ret = chdir(d);
	}
	else if (_comparestr(info->argv[1], "-") == 0)
	{
		if (!envGet(info, "OLDPWD="))
		{
			_puts(st);
			_putchar('\n');
			return (1);
		}
		_puts(envGet(info, "OLDPWD=")), _putchar('\n');
		chd_ret = /* TODO: what should this be? */
			chdir((d = envGet(info, "OLDPWD=")) ? d : "/");
	}
	else
		chd_ret = chdir(info->argv[1]);
	if (chd_ret == -1)
	{
		_putsError(info, "can't cd to ");
		_iputs(info->argv[1]), _iputchar('\n');
	}
	else
	{
		envSet(info, "OLDPWD", envGet(info, "PWD="));
		envSet(info, "PWD", getcwd(b, 1024));
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
	char **ag_arr;

	ag_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ag_arr); /* temp att_unused workaround */
	return (0);
}
