/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 13:22:14 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/03 15:12:00 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes(char *line, int index)
{
	int	i;
	int	is_open;

	i = 0;
	is_open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (is_open == 0 && line[i] == '\"')
			is_open = 1;
		else if (is_open == 0 && line[i] == '\'')
			is_open = 2;
		else if (is_open == 1 && line[i] == '\"')
			is_open = 0;
		else if (is_open == 2 && line[i] == '\'')
			is_open = 0;
		i++;
	}
	return (is_open);
}

int	quote_check(t_shell *shell, char **line)
{
	if (quotes(*line, __INT_MAX__))
	{
		ft_putendl_fd("minishell: syntax error - quotes not closed", STDERR);
		ft_memdel(*line);
		shell->rv = 2;
		shell->start = NULL;
		return (1);
	}
	return (0);
}

char	*space_alloc(char *line)
{
	char	*new;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_separator(line, i))
			count++;
		i++;
	}
	new = malloc(sizeof(char) * (i + 2 * count + 1));
	return (new);
}

static void	copy_and_increment_char(char *new, char *line, int *i, int *j)
{
	new[*j] = line[*i];
	(*j)++;
	(*i)++;
}

char	*space_out_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) == 0 && is_separator(line, i))
		{
			new[j] = ' ';
			j++;
			copy_and_increment_char(new, line, &i, &j);
			if (quotes(line, i) == 0 && (line[i] == '>' || line[i] == '<'))
				copy_and_increment_char(new, line, &i, &j);
			new[j] = ' ';
			j++;
		}
		else
			copy_and_increment_char(new, line, &i, &j);
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}
