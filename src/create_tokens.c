/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 16:15:39 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/18 11:46:43 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_to_quote(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (i + 1);
}

t_token	*make_token(char *line, int *i, t_shell *shell)
{
	t_token	*token;
	int		j;

	j = 0;
	token = malloc(sizeof(t_token));
	while (line[*i + j] && (line[*i + j] != ' '))
	{
		if (line[*i + j] == '\\' && (line[*i + j + 1] == '\'' \
			|| line[*i + j + 1] == '\"'))
			j++;
		else if (line[*i + j] == '\'' || line[*i + j] == '\"')
			j += skip_to_quote(line + *i + j + 1, line[*i + j]);
		j++;
	}
	token->str = repl_process(ft_substr(line, *i, j), shell);
	*i += j;
	return (token);
}

void	apply_token_type(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<<") == 0 && separator == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*create_tokens(char *line, t_shell *shell)
{
	t_token	*token;
	t_token	*prev;
	int		i;
	int		separator;

	prev = NULL;
	token = NULL;
	i = 0;
	skip_space(line, &i);
	while (line[i])
	{
		separator = find_separator(line, i);
		token = make_token(line, &i, shell);
		token->prev = prev;
		if (prev != NULL)
			prev->next = token;
		prev = token;
		apply_token_type(token, separator);
		token->str = strip_quotes(token->str);
		skip_space(line, &i);
	}
	if (token)
		token->next = NULL;
	while (token && token->prev)
		token = token->prev;
	return (token);
}
