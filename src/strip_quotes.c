/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strip_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 09:57:47 by bmans         #+#    #+#                 */
/*   Updated: 2021/11/11 10:32:23 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_to_quote(int i, char *str, char to_find)
{
	int		count;

	count = 1;
	while (str[i])
	{
		if (str[i] == to_find)
			return (i);
		if (str[i] == '\\')
			i++;
		i++;
	}
	return (i);
}

char	*strip_quotes(char *str)
{
	char	*temp[2];
	int		i[2];
	int		bypass;

	ft_bzero(i, sizeof(int) * 2);
	bypass = 0;
	temp[0] = malloc(ft_strlen(str));
	while (str[i[0]])
	{
		if ((str[i[0]] != '\"' && str[i[0]] != '\'') || i[0] < bypass)
		{
			if ((str[i[0] + 1] == '\"' || str[i[0] + 1] == '\'') \
				&& str[i[0]] == '\\' && i[0] >= bypass)
				i[0]++;
			temp[0][i[1]] = str[i[0]];
			i[1]++;
		}
		else if (i[0] == 0 || (i[0] > 0 && str[i[0] - 1] != '\\' \
			&& i[0] != bypass))
			bypass = skip_to_quote(i[0] + 1, str, str[i[0]]);
		i[0]++;
	}
	temp[1] = ft_substr(temp[0], 0, i[1]);
	free(temp[0]);
	return (temp[1]);
}
