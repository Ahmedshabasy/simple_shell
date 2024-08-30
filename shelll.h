#ifndef SHELLL_H
#define SHELLL_H

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
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONV_LOWERCASE	1
#define CONV_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct lsts - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct lsts
{
	int num;
	char *str;
	struct lsts *next;
} lst_t;

/**
 *struct psnfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@ln_count: the error count
 *@err_num: the error code for exit()s
 *@lncount_flg: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buf, on if chaining
 *@cmd_buff_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *pth;
	int argc;
	unsigned int ln_cnt;
	int err_num;
	int lncount_flg;
	char *fname;
	lst_t *env;
	lst_t *history;
	lst_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buff; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buff_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} inf_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct bltn
{
	char *type;
	int (*func)(inf_t *);
} bltn_table;


/* hsh.c */
int hsh(inf_t *, char **);
int find_bltn(inf_t *);
void find_cmd(inf_t *);
void fork_cmd(inf_t *);

/* path.c */
int is_cmd(inf_t *, char *);
char *dap_chars(char *, int, int);
char *find_pth(inf_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputss(char *);
int _eputchr(char);
int _putsfd(char c, int fd);
int _putssfd(char *str, int fd);

/* string_functions.c */
int _sln(char *);
int _scm(char *, char *);
char *beg_wiz(const char *, const char *);
char *_sct(char *, char *);

/* string_functions2.c */
char *_scopy(char *, char *);
char *_sdap(const char *);
void _puts(char *);
int _putchr(char);

/* string_functions3.c */
char *_sncopy(char *, char *, int);
char *_snct(char *, char *, int);
char *_schr(char *, char);

/* string_functions4.c */
char **sto(char *, char *);
char **sto2(char *, char);

/* memory_functions */
char *_memset(char *, char, unsigned int);
void funcfree(char **);
void *_rallc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int pofree(void **);

/* more_functions.c */
int inractve(inf_t *);
int is_dlm(char, char *);
int _isalpa(int);
int _atoi(char *);

/* more_functions2.c */
int _eratoi(char *);
void pnt_err(inf_t *, char *);
int print_d(int, int);
char *conv_number(long int, int, int);
void rm_com(char *);

/* builtin_emulators.c */
int _myexit(inf_t *);
int _mycd(inf_t *);
int _myhelp(inf_t *);

/* builtin_emulators2.c */
int _myhistory(inf_t *);
int _myalias(inf_t *);

/* getline.c module */
ssize_t get_input(inf_t *);
int _getln(inf_t *, char **, size_t *);
void sigintHandler(int);

/* info.c module */
void clear_inf(inf_t *);
void set_inf(inf_t *, char **);
void free_inf(inf_t *, int);

/* env.c module */
char *_getenv(inf_t *, const char *);
int _myenv(inf_t *);
int _mysetenv(inf_t *);
int _myunsetenv(inf_t *);
int populate_env_lst(inf_t *);

/* env2.c module */
char **get_environ(inf_t *);
int _unsetenv(inf_t *, char *);
int _setenv(inf_t *, char *, char *);

/* file_io_functions.c */
char *get_history_file(inf_t *inf);
int write_history(inf_t *inf);
int read_history(inf_t *inf);
int build_history_lst(inf_t *inf, char *buff, int lncount);
int renumber_history(inf_t *inf);

/* liststr.c module */
lst_t *plus_node(lst_t **, const char *, int);
lst_t *plus_node_end(lst_t **, const char *, int);
size_t pnt_lst_str(const lst_t *);
int del_node_at_i(lst_t **, unsigned int);
void free_lst(lst_t **);

/* liststr2.c module */
size_t lst_ln(const lst_t *);
char **lst_to_strings(lst_t *);
size_t pnt_lst(const lst_t *);
lst_t *node_big_wiz(lst_t *, char *, char);
ssize_t get_node_index(lst_t *, lst_t *);

/* chain.c */
int is_chain(inf_t *, char *, size_t *);
void check_chain(inf_t *, char *, size_t *, size_t, size_t);
int replace_alias(inf_t *);
int replace_vars(inf_t *);
int replace_string(char **, char *);

#endif
