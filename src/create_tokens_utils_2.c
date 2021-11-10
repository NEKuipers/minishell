/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens_utils_2.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 13:34:06 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/10 12:39:03 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_separator(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr(";|<>", line[i]))
		return (0);
	else if (ft_strchr(";|<>", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

void	skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t') \
			|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int	find_separator(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && \
			ft_strchr(";|><", line[i + 1]))
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>' \
			&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = previous_separator(token, 0);
		if (!prev || is_type(prev, END) || is_type(prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

char	*strip_quotes(char *str)
{
	char	*temp[2];
	int		i;
	int		len;
	int		bypass;

	i = 0;
	len = 0;
	bypass = 0;
	temp[0] = malloc(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\''))
			i++;
		else if ((str[i] != '\"' && str[i] != '\'') || i < bypass)
		{
			temp[0][len] = str[i];
			len++;
		}
		else
			bypass = ft_strchr(str + i + 1, str[i]) - str;
		i++;
	}
	temp[1] = ft_substr(temp[0], 0, len);
	free(temp[0]);
	return (temp[1]);
}
