/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 16:16:41 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/18 14:46:13 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_part_two(t_shell *shell, char *line)
{
	t_token	*token;

	line = space_out_line(line);
	shell->start = create_tokens(line, shell);
	free(line);
	arrange_tokens(shell);
	token = shell->start;
	if (is_type(token, ARG))
		apply_token_type(token, 0);
}

void	parse(t_shell *shell)
{
	char	*line;

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
	parse_part_two(shell, line);
}

static void	syntax_errormessage(char *str, int type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
	if (type == 1)
		ft_putstr_fd("newline", STDERR);
	else if (type == 2)
		ft_putstr_fd(str, STDERR);
	ft_putendl_fd("'", STDERR);
}

int	check_syntax(t_shell *shell, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAIH") \
			&& (!token->next || is_types(token->next, "TAHPE")))
		{
			if (token->next)
				syntax_errormessage(token->next->str, 2);
			else
				syntax_errormessage(NULL, 1);
			shell->rv = 258;
			return (0);
		}
		if (is_types(token, "PE") \
			&& (!token->prev || !token->next || \
				is_types(token->prev, "TAIHPE")))
		{
			syntax_errormessage(token->str, 2);
			shell->rv = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}
