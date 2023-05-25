#ifndef MY_SHELL_H_
#define MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* for loop.c */
int hsh(info_t *info, char **argvec);
int locate_builtin(info_t *info);
void get_cmd(info_t *info);
void fork_process(info_t *info);

/* for_parser.c */
int cmd_check(info_t *, char *file_path);
char *clone_chars(char *, int, int);
char *get_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* for_errors.c */
void _iputs(char *);
int _iputchar(char);
int _writefd(char a, int fileDescriptor);
int _printsfd(char *strn, int fileDescriptor);

/* for_string.c */
int _strlength(char *st);
int _comparestr(char *str1, char *str2);
char *begins_with(const char *haystk, const char *ndl);
char *cat_str(char *buf_dest, char *buf_src);

/* for_string1.c */
char *cpy_str(char *destination, char *source);
char *str_clone(const char *strn);
void _puts(char *strn);
int _putchar(char a);

/* for_exits.c */
char *_cpystrn(char *strdest, char *strsrc, int num);
char *_catstrn(char *strdest, char *strsrc, int num);
char *_chrstr(char *strn, char a);

/* for_tokenizer.c */
char **str_split(char *strn, char *d);
char **str_split2(char *strn, char d);

/*for_realloc.c */
char *set_memory(char *mem, char a, unsigned int k);
void free_string_set(char **ss);
void *realloc_mem(void *mem_ptr, unsigned int prev_size, unsigned int curr_size);

/* for_memory.c */
int _freeptr(void **p);

/* for_atoi.c */
int _interactmode(info_t *info);
int isDelimiter(char i, char *de_lim);
int isAlphabet(int b);
int atoi_(char *strn);

/* for_errors1.c */
int ErrCheckAtoi(char *strn);
void _putsError(info_t *argInfo, char *estrn);
int print_decimal(int userInput, int fileDescriptor);
char *convertNum(long int digit, int baseNum, int argFlags);
void filterComments(char *strbuf);

/* for_builtin.c */
int exit_shell(info_t *info);
int changeDir(info_t *info);
int my_help(info_t *info);

/* for_builtin1.c */
int historyData(info_t *info);
int aliasUnset(info_t *info, char *strn);
int aliasSet(info_t *info, char *strn);
int aliasPrint(list_t *alias_node);
int myAlias(info_t *info);


/* for_getinfo.c */
void infoReset(info_t *info);
void infoSet(info_t *info, char **argvect);
void infoFree(info_t *info, int all_fields);

/* for_environ.c */
char *envGet(info_t *info, const char *env_name);
int envPrint(info_t *info);
int setEnv(info_t *info);
int unsetEnv(info_t *info);
int FillEnvData(info_t *info);

/* for_getenv.c */
char **getEnviron(info_t *info);
int envUnset(info_t *info, char *env_var);
int envSet(info_t *info, char *strvar, char *str_value);

/* for_history.c */
char *FetchHistFile(info_t *argInfo);
int store_history(info_t *argInfo);
int access_history(info_t *argInfo);
int updateHistList(info_t *argInfo, char *buff, int linecount);
int reindexHist(info_t *argInfo);

/* for_lists.c */
list_t *addNewNode(list_t **hd_node, const char *strn, int index);
list_t *appendNode(list_t **hd_node, const char *strn, int index);
size_t DisplayStrList(const list_t *ptr_h);
int remove_node_at_index(list_t **hd_node, unsigned int nd_index);
void clear_list(list_t **hd_ptr);

/* for_lists1.c */
size_t list_size(const list_t *hd_node);
char **list_to_text(list_t *head_ptr);
size_t display_list(const list_t *hd_node);
list_t *node_begins_with(list_t *ls_node, char *prefix_str, char a);
ssize_t locate_node_index(list_t *head_ptr, list_t *node_ptr);

/* for_vars.c */
int is_chain_delimiter(info_t *info, char *buff, size_t *ptr);
void _checkchainstatus (info_t *info, char *buff, size_t *ptr, size_t init, size_t buf_len);
int change_alias(info_t *info);
int change_vars(info_t *info);
int change_string(char **prev, char *updated);

/* for_getline.c */
ssize_t inputBuffer(info_t *f, char **buff, size_t *l);
ssize_t readInput(info_t *info);
ssize_t readBuff(info_t *info, char *buff, size_t *j);
int getLine(info_t *info, char **ptr, size_t *len_buff);
void sigintHandler(__attribute__((unused))int sig_num);
#endif
