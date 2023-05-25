#include "shell.h"

/**
* hsh - main shell loop
* @info: the parameter & return info struct
* @argvec: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh(info_t *info, char **argvec)
{
ssize_t y = 0;
int builtin_result = 0;

while (y != -1 && builtin_result != -2)
{
infoReset(info);
if (_interactmode(info))
_puts("$ ");
_iputchar(BUF_FLUSH);
y = readInput(info);
if (y != -1)
{
infoSet(info, argvec);
builtin_result = locate_builtin(info);
if (builtin_result == -1)
get_cmd(info);
}
else if (_interactmode(info))
_putchar('\n');
infoFree(info, 0);
}
store_history(info);
infoFree(info, 1);
if (!_interactmode(info) && info->status)
exit(info->status);
if (builtin_result == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_result);
}

/**
* locate_builtin - finds a builtin command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
*			0 if builtin executed successfully,
*			1 if builtin found but not successful,
*			-2 if builtin signals exit()
*/
int locate_builtin(info_t *info)
{
int j, built_in_result = -1;
builtin_table built_in_tbl[] = {
{"exit", exit_shell},
{"env", envPrint},
{"help", my_help},
{"history", historyData},
{"setenv", setEnv},
{"unsetenv", unsetEnv},
{"cd", changeDir},
{"alias", myAlias},
{NULL, NULL}
};

for (j = 0; built_in_tbl[j].type; j++)
if (_comparestr(info->argv[0], built_in_tbl[j].type) == 0)
{
info->line_count++;
built_in_result = built_in_tbl[j].func(info);
break;
}
return (built_in_result);
}

/**
* get_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void get_cmd(info_t *info)
{
char *f_path = NULL;
int m, p;

info->line_count++;
info->linecount_flag = 0;

for (m = 0, p = 0; info->arg[m]; m++)
{
if (!isDelimiter(info->arg[m], " \t\n"))
p++;
}

if (!p)
{
return;
}

f_path = get_path(info, envGet(info, "PATH="), info->argv[0]);
if (f_path)
{
info->path = f_path;
fork_process(info);
}
else
{
if ((_interactmode(info) || envGet(info, "PATH=") ||
info->argv[0][0] == '/') && cmd_check(info, info->argv[0]))
{
fork_process(info);
}
else if (*(info->arg) != '\n')
{
info->status = 127;
_putsError(info, "not found\n");
}
}
}

/**
* fork_process - forks a an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void fork_process(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, getEnviron(info)) == -1)
{
infoFree(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
_putsError(info, "Permission denied\n");
}
}
}
