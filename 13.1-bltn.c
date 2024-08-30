#include "shelll.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(inf_t *inf)
{
	pnt_lst(inf->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(inf_t *inf, char *str)
{
	char *p, c;
	int ret;

	p = _schr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_node_at_i(&(inf->alias),
		get_node_i(inf->alias, node_big_wiz(inf->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(inf_t *inf, char *str)
{
	char *p;

	p = _schr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (plus_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(lst_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _schr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchr(*a);
		_putchr('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(inf_t *inf)
{
	int i = 0;
	char *p = NULL;
	lst_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		p = _schr(inf->argv[i], '=');
		if (p)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(node_big_wiz(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
