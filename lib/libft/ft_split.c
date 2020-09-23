/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:28:15 by nkuipers       #+#    #+#                */
/*   Updated: 2019/11/11 12:12:24 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		*free_all(char **strings)
{
	int i;

	i = 0;
	while (strings[i] != 0)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return (NULL);
}

static int		segcount(char *s, char c)
{
	int in_string;
	int count;

	in_string = 0;
	count = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			in_string = 0;
		if (*s != c && in_string == 0)
		{
			in_string = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int		seglen(char *s, int i, char c)
{
	int length;

	length = 0;
	while (s[i] != c && s[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

static char		**makestrings(char **strings, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < segcount((char *)s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		strings[j] = (char*)malloc(sizeof(char) * seglen((char *)s, i, c) + 1);
		if (!(strings[j]))
			return (free_all(strings));
		while (s[i] != c && s[i] != '\0')
		{
			strings[j][k] = s[i];
			k++;
			i++;
		}
		strings[j][k] = '\0';
		j++;
	}
	strings[j] = 0;
	return (strings);
}

char			**ft_split(char const *s, char c)
{
	char	**strings;

	strings = (char**)malloc(sizeof(char*) * (segcount((char *)s, c) + 1));
	if (!(strings) || !(s))
		return (0);
	strings = makestrings(strings, s, c);
	return (strings);
}
