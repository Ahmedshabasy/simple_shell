#include "shelll.h"

/**
 * input_buff - buffers chained commands
 * @inf: parameter struct
 * @buff: address of buffer
 * @ln: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(inf_t *inf, char **buff, size_t *ln)
{
	ssize_t r = 0;
	size_t ln_p = 0;

	if (!*ln) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &ln_p, stdin);
#else
		r = getline(inf_t, char **, &size_t);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			inf->lncount_flg = 1;
			rm_com(*buff);
			build_history_lst(inf, *buff, inf->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*ln = r;
				inf->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(inf_t *inf)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t i, j, ln;
	ssize_t r = 0;
	char **buff_p = &(inf->arg), *p;

	_putchr(BUFF_FLUSH);
	r = input_buff(inf, &buff, &ln);
	if (r == -1) /* EOF */
		return (-1);
	if (ln)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buff + i; /* get pointer for return */

		check_chain(inf, buff, &j, i, ln);
		while (j < ln) /* iterate to semicolon or end */
		{
			if (is_chain(inf, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= ln) /* reached end of buffer? */
		{
			i = ln = 0; /* reset position and length */
			inf->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p; /* pass back pointer to current command position */
		return (_sln(p)); /* return length of current command */
	}

	*buff_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buff - reads a buffer
 * @inf: parameter struct
 * @buff: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buff(inf_t *inf, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(inf->readfd, buff, READ_BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @ln: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(inf_t *inf, char **ptr, size_t *ln)
{
	static char buff[READ_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && len)
		s = *ln;
	if (i == len)
		i = len = 0;

	r = read_buff(inf, buff, &ln);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _schr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _rallc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_sct(new_p, buff + i, k - i);
	else
		_scopy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (len)
		*ln = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchr(BUFF_FLUSH);
}
