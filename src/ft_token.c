/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_token.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 15:59:22 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 15:27:40 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** This is a modified ft_split that takes two characters, in this case ' ' and
** '\t', in order to correctly cut out the arguments entered in the cmd line.
*/

static void		*free_all(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int		segcount(char *s, char c, char d)
{
	int in_string;
	int count;

	in_string = 0;
	count = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == c || *s == d)
			in_string = 0;
		if (*s != c && *s != d && in_string == 0)
		{
			in_string = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int		seglen(char *s, int i, char c, char d)
{
	int length;

	length = 0;
	while (s[i] != c && s[i] != d && s[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

static char		**makestrs(char **strs, char const *s, char c, char d)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < segcount((char *)s, c, d))
	{
		k = 0;
		while (s[i] == c || s[i] == d)
			i++;
		strs[j] = (char*)malloc(sizeof(char) * seglen((char *)s, i, c, d) + 1);
		if (!(strs[j]))
			return (free_all(strs));
		while (s[i] != c && s[i] != d && s[i] != '\0')
		{
			strs[j][k] = s[i];
			k++;
			i++;
		}
		strs[j][k] = '\0';
		j++;
	}
	strs[j] = 0;
	return (strs);
}

char			**ft_token(char const *s, char c, char d)
{
	char	**strs;

	strs = (char**)malloc(sizeof(char*) * (segcount((char *)s, c, d) + 1));
	if (!(strs) || !(s))
		return (0);
	strs = makestrs(strs, s, c, d);
	return (strs);
}
