#include "shelll.h"

/**
 * _scopy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_scopy(char *dest, char *src)
{
	int n = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[n])
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}

/**
 * _sdap - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_sdap(const char *str)
{
	int ln = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		ln++;
	ret = malloc(sizeof(char) * (ln + 1));
	if (!ret)
		return (NULL);
	for (ln++; ln--;)
		ret[ln] = *--str;
	return (ret);
}

/**
 *_putss - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _putss(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_putchar(str[n]);
		n++;
	}
}

/**
 * _putchr - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchr(char c)
{
	static int n;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buff, n);
		n = 0;
	}
	if (c != BUFF_FLUSH)
		buff[n++] = c;
	return (1);
}
