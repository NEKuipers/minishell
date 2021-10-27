/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 16:16:41 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/27 14:26:06 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	is_types(t_token *token, char *types)
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

void	parse(t_shell *shell)
{
	char	*line;
	t_token	*token;

//	ft_putstr_fd("<$ ", STDERR);
//	if (get_next_line(0, &line) == -1 && (shell->exit = 1))
//		ft_putendl_fd("exit", STDERR);
	line = readline("<$ ");
	if (line == NULL)
	{
		rl_replace_line("", 0);
		shell->exit = 1;
		ft_putendl_fd("exit", STDERR);
		line = ft_strdup("");
	}
	else
		add_history(line);
	if (g_signal.sigint == 1)
		shell->rv = g_signal.exit_status;
	if (quote_check(shell, &line))
		return ;
	rl_redisplay();
	line = repl_process(line, shell);
	line = space_out_line(line);
	shell->start = create_tokens(line);
	free(line);
	arrange_tokens(shell);
	token = shell->start;
	while (token)
	{
		if (is_type(token, ARG))
			apply_token_type(token, 0);
		token = token->next;
	}	
}

int	check_line(t_shell *shell, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI") \
			&& (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			if (token->next)
				ft_putstr_fd(token->next->str, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			shell->rv = 258;
			return (0);
		}
		if (is_types(token, "PE") \
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
