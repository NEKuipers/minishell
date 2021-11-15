/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 16:15:39 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/15 15:07:43 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		//if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
		if (c == ' ' && line[*i + j] == '\"')
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

static t_token	*init_token(char *line, int *i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
//	token->squote = 0;
	token->str = (char *)malloc(sizeof(char) * next_alloc(line, i));
	return (token);
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = init_token(line, i);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
//		if (line[*i] == '\'')
//			token->squote = 1;
//		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
		if (c == ' ' && line[*i] == '\"')
			c = line[(*i)];
		else if (c != ' ' && line[*i] == c)
			c = ' ';
		else
		{
			token->str[j] = line[(*i)];
			j++;
		}
		(*i)++;
	}
	token->str[j] = '\0';
	return (token);
}
*/

int	skip_to_quote(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (i + 1);
}

t_token	*make_token(char *line, int *i, t_shell *shell)
{
	t_token	*token;
	char	*temp;
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
	temp = repl_process(ft_substr(line, *i, j), shell);
	token->str = strip_quotes(temp);
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
		skip_space(line, &i);
	}
	if (token)
		token->next = NULL;
	while (token && token->prev)
		token = token->prev;
	return (token);
}
