#include "shelll.h"

/**
 * clr_inf - initializes info_t struct
 * @inf: struct address
 */
void clr_inf(inf_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * st_inf - initializes info_t struct
 * @inf: struct address
 * @av: argument vector
 */
void st_inf(inf_t *inf, char **av)
{
	int i = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = sto(info->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _sdap(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * free_inf - frees info_t struct fields
 * @inf: struct address
 * @all: true if freeing all fields
 */
void free_inf(inf_t *inf, int all)
{
	free(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmd_buff)
			free(inf->arg);
		if (inf->env)
			free_lst(&(inf->env));
		if (inf->history)
			free_lst(&(inf->history));
		if (inf->alias)
			free_lst(&(inf->alias));
		free(inf->environ);
			inf->environ = NULL;
		pofree((void **)inf->cmd_buff);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUFF_FLUSH);
	}
}
