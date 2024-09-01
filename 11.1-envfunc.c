#include "shelll.h"

/**
 * get_environ - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(inf_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = lst_in(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(inf_t *inf, char *var)
{
	lst_t *node = inf->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = beg_wiz(node->str, var);
		if (p && *p == '=')
		{
			inf->env_changed = del_node_at_i(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(inf_t *inf, char *var, char *value)
{
	char *buff = NULL;
	lst_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buff = malloc(_sln(var) + _sln(value) + 2);
	if (!buff)
		return (1);
	_scopy(buff, var);
	_sct(buff, "=");
	_sct(buff, value);
	node = inf->env;
	while (node)
	{
		p = beg_wiz(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	plus_node_end(&(inf->env), buff, 0);
	free(buff);
	inf->env_changed = 1;
	return (0);
}
