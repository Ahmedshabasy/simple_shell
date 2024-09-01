#include "shelll.h"

/**
 * **sto - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **sto(char *str, char *d)
{
	int a, b, c, e, nword = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_dlm(str[a], d) && (is_dlm(str[a + 1], d) || !str[a + 1]))
			nword++;

	if (nword == 0)
		return (NULL);
	s = malloc((1 + nword) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < nword; b++)
	{
		while (is_dlm(str[a], d))
			a++;
		c = 0;
		while (!is_dlm(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **sto2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **sto2(char *str, char d)
{
	int a, b, c, e, nword = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			nword++;
	if (nword == 0)
		return (NULL);
	s = malloc((1 + nword) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < nword; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}
