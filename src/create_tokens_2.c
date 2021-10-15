/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 16:16:41 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/15 14:52:18 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int quotes(char *line, int index)
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

int quote_check(t_shell *shell, char **line)
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

int		is_separator(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr(";|<>", line[i]))
		return (0);
	else if (ft_strchr(";|<>", line[i]) && quotes(line, i) == 0)
		return (1);
	else
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
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

void	skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int		find_separator(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && \
			ft_strchr(";|><", line[i + 1]))
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
				&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

t_token	*next_separator(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*previous_separator(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int		is_types(t_token *token, char *types)
{
	if (ft_strchr(types, ' ') && is_type(token, EMPTY))
		return (1);
	else if (ft_strchr(types, 'X') && is_type(token, CMD))
		return (1);
	else if (ft_strchr(types, 'x') && is_type(token, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && is_type(token, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && is_type(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && is_type(token, INPUT))
		return (1);
	else if (ft_strchr(types, 'P') && is_type(token, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && is_type(token, END))
		return (1);
	return (0);
}

int		is_last_valid_arg(t_token *token)
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

void	squish_args(t_shell *shell)
{
	t_token	*token;
	t_token	*prev;

	token = shell->start;
	while (token)
	{
		prev = previous_separator(token, 0);
		if (is_type(token, ARG) && is_types(prev, "TAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			token->next = (prev) ? prev->next : shell->start;
			prev = (prev) ? prev : token;
			prev->next->prev = token;
			prev->next = (shell->start->prev) ? prev->next : token;
			shell->start = (shell->start->prev) ? shell->start->prev : shell->start;
		}
		token = token->next;
	}
}

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	parse(t_shell *shell)
{
	char	*line;
	t_token	*token;

//	ft_putstr_fd("<$ ", STDERR);
//	if (get_next_line(0, &line) == -1 && (shell->exit = 1))
//		ft_putendl_fd("exit", STDERR);
	line = readline("<$ ");
	if (line == NULL && shell->exit == 1)
		ft_putendl_fd("exit", STDERR);
	add_history(line);
	if (g_signal.sigint == 1)
		shell->rv = g_signal.exit_status;
	if (quote_check(shell, &line))
		return ;
	rl_redisplay();
	line = space_out_line(line);
	shell->start = create_tokens(line);
	free(line);
	squish_args(shell);
	token = shell->start;
	while (token)
	{
		if (is_type(token, ARG))
			apply_token_type(token, 0);
		token = token->next;
	}
}

int		check_line(t_shell *shell, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI")
		&& (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			token->next ? ft_putstr_fd(token->next->str, STDERR) : 0;
			token->next ? 0 : ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			shell->rv = 258;
			return (0);
		}
		if (is_types(token, "PE")
		&& (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			shell->rv = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}
