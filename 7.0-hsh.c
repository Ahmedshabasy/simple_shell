#include "shelll.h"

/**
 * hsh - main shell loop
 * @inf: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(inf_t *inf, char **av)
{
	ssize_t b = 0;
	int bltn_ret = 0;

	while (b != -1 && bltn_ret != -2)
	{
		clear_inf(inf);
		if (inractve(inf))
			_puts("$ ");
		_eputchr(BUFF_FLUSH);
		b = get_input(inf);
		if (b != -1)
		{
			set_inf(inf, av);
			bltn_ret = find_bltn(inf);
			if (bltn_ret == -1)
				find_cmd(inf);
		}
		else if (intractv(inf))
			_putchr('\n');
		free_inf(inf, 0);
	}
	write_history(inf);
	free_inf(inf, 1);
	if (!intractv(inf) && inf->status)
		exit(inf->status);
	if (bltn_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (bltn_ret);
}

/**
 * find_bltn - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_bltn(inf_t *inf)
{
	int n, blt_in_ret = -1;
	bltn_table bltntbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; bltntbl[n].type; n++)
		if (_scm(inf->argv[0], bltntbl[n].type) == 0)
		{
			inf->ln_cnt++;
			blt_in_ret = bltntbl[n].func(inf);
			break;
		}
	return (blt_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(inf_t *inf)
{
	char *pth = NULL;
	int a, b;

	inf->pth = inf->argv[0];
	if (inf->lncount_flg == 1)
	{
		inf->ln_cnt++;
		inf->lncount_flg = 0;
	}
	for (a = 0, b = 0; inf->arg[a]; a++)
		if (!is_dlm(inf->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	pth = find_pth(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (pth)
	{
		inf->pth = pth;
		fork_cmd(inf);
	}
	else
	{
		if ((intractv(inf) || _getenv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			pnt_err(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(inf_t *inf)
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
		if (execve(inf->pth, inf->argv, get_environ(inf)) == -1)
		{
			free_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				pnt_err(inf, "Permission denied\n");
		}
	}
}
