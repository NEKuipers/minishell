/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strip_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/15 11:35:00 by bmans         #+#    #+#                 */
/*   Updated: 2021/11/16 14:16:13 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	strip_double_quotes(int *i, int *j, char *str, char *tmp)
{
	int	k;
	int	len;

	len = skip_to_quote(str + *i + 1, '\"');
	k = 1;
	while (k < len)
	{
		if (!ft_strncmp(str + *i + k, "\\\"", 2))
			k++;
		tmp[*j] = str[*i + k];
		(*j)++;
		k++;
	}
	*i += len - 1;
}

static void	strip_single_quotes(int *i, int *j, char *str, char *tmp)
{
	int	k;

	k = skip_to_quote(str + *i + 1, '\'');
	ft_strlcpy(tmp + *j, str + *i + 1, k);
	*i += k;
	*j += k - 1;
}

static void	strip_quotes_loop(int *i, int *j, char *str, char *tmp)
{
	if (!ft_strncmp(str + *i, "\\\'", 2) || !ft_strncmp(str + *i, "\\\"", 2))
		(*i)++;
	if (str[*i] == '\"')
		strip_double_quotes(i, j, str, tmp);
	else if (str[*i] == '\'')
		strip_single_quotes(i, j, str, tmp);
	else
	{
		tmp[*j] = str[*i];
		(*j)++;
	}
	(*i)++;
}

char	*strip_quotes(char *str)
{
	char	*out;
	char	*tmp;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	tmp = malloc(len + 1);
	if (!tmp)
		return (str);
	ft_bzero(tmp, len + 1);
	i = 0;
	j = 0;
	while (i < len)
		strip_quotes_loop(&i, &j, str, tmp);
	out = ft_strdup(tmp);
	free(tmp);
	free(str);
	return (out);
}
