#include "shelll.h"

/**
 * intractv - returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int intractv(inf_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_dlm - checks if character is a delimeter
 * @c: the char to check
 * @dlm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_dlm(char c, char *dlm)
{
	while (*dlm)
		if (*dlm++ == c)
			return (1);
	return (0);
}

/**
 *_isalp - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalp(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int n, sign = 1, flg = 0, outpt;
	unsigned int rslt = 0;

	for (n = 0;  s[n] != '\0' && flg != 2; n++)
	{
		if (s[n] == '-')
			sign *= -n;

		if (s[n] >= '0' && s[n] <= '9')
		{
			flg = 1;
			rslt *= 10;
			rslt += (s[n] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sign == -1)
		outpt = -rslt;
	else
		outpt = rslt;

	return (outpt);
}
