#include "shelll.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(inf_t *inf, char *buff, size_t *p)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buff_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buff_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		inf->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @ln: length of buf
 *
 * Return: Void
 */
void check_chain(infot *inf, char *buff, size_t *p, size_t i, size_t ln)
{
	size_t j = *p;

	if (inf->cmd_buff_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[i] = 0;
			j = ln;
		}
	}
	if (inf->cmd_buff_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[i] = 0;
			j = ln;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(inf_t *inf)
{
	int i;
	lst_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_big_wz(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = _schr(node->str, '=');
		if (!p)
			return (0);
		p = _sdap(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(inf_t *inf)
{
	int i = 0;
	lst_t *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_scm(info->argv[i], "$?"))
		{
			replace_string(&(inf->argv[i]),
				_sdap(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_scm(inf->argv[i], "$$"))
		{
			replace_string(&(inf->argv[i]),
				_sdap(conv_number(getpid(), 10, 0)));
			continue;
		}
		node = node_big_wiz(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[i]),
				_sdap(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[i], _sdap(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
