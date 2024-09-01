#include "shelll.h"

/**
 * is_cmd - determines if a file is an executable command
 * @inf: the info struct
 * @pth: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(inf_t *inf, char *pth)
{
	struct stat st;

	(void)inf;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dap_chars - duplicates characters
 * @pthstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dap_chars(char *pthstr, int start, int stop)
{
	static char buff[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pthstr[a] != ':')
			buff[b++] = pthstr[a];
	buff[b] = 0;
	return (buff);
}

/**
 * fnd_pth - finds this cmd in the PATH string
 * @inf: the info struct
 * @pthstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *fnd_pth(inf_t *inf, char *pthstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((_sln(cmd) > 2) && beg_wiz(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[i] || pthstr[i] == ':')
		{
			pth = dap_chars(pthstr, curr_pos, i);
			if (!*pth)
				_sct(pth, cmd);
			else
			{
				_sct(pth, "/");
				_sct(pth, cmd);
			}
			if (is_cmd(inf, pth))
				return (pth);
			if (!pthstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
