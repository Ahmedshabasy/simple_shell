#include "shelll.h"

/**
 * _myexit - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(inf_t *inf)
{
	int exitcheck;

	if (inf->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _eratoi(inf->argv[1]);
		if (exitcheck == -1)
		{
			inf->status = 2;
			pnt_err(inf, "Illegal number: ");
			_eputss(inf->argv[1]);
			_eputchr('\n');
			return (1);
		}
		inf->err_num = _eratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(inf_t *inf)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenv(inf, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_scm(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(s);
			_putchr('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchr('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
	{
		pnt_err(inf, "can't cd to ");
		_eputss(inf->argv[1]), _eputchr('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(inf_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
