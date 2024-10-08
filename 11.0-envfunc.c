#include "shelll.h"

/**
 * _myenv - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(inf_t *inf)
{
	pnt_lst(inf->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(inf_t *inf, const char *name)
{
	lst_t *node = inf->env;
	char *p;

	while (node)
	{
		p = beg_wiz(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(inf_t *inf)
{
	if (inf->argc != 3)
	{
		_eputss("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(inf_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eputss("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_env_lst - populates env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_lst(inf_t *inf)
{
	lst_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		plus_node_end(&node, environ[i], 0);
	inf->env = node;
	return (0);
}
