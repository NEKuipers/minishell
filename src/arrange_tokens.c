/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arrange_tokens.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 13:37:31 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/03 10:10:43 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	arrange_tokens_two(t_shell *shell, t_token *token, t_token *prev)
{
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = prev;
	if (prev)
		token->next = prev->next;
	else
		token->next = shell->start;
	if (!prev)
		prev = token;
	prev->next->prev = token;
	if (!shell->start->prev)
		prev->next = token;
	if (shell->start->prev)
		shell->start = shell->start->prev;
	
}

void	arrange_tokens(t_shell *shell)
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
			arrange_tokens_two(shell, token, prev);
		}
		token = token->next;
	}
}
