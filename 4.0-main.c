#include "shelll.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	inf_t inf[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputss(av[0]);
				_eputss(": 0: Can't open ");
				_eputss(av[1]);
				_eputchr('\n');
				_eputchr(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = fd;
	}
	populate_env_lst(inf);
	read_history(inf);
	hsh(inf, av);
	return (EXIT_SUCCESS);
}
