/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 16:15:39 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/10 14:11:23 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	token->str = (char *)malloc(sizeof(char) * next_alloc(line, i));
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)];
		else if (c != ' ' && line[*i] == c)
			c = ' ';
		token->str[j] = line[(*i)];
		j++;
		(*i)++;
	}
	token->str[j] = '\0';
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

static t_token	*process_token(char *line, int *i, t_shell *shell)
{
	t_token	*temp;
<<<<<<< HEAD
	char	*temp_str;	

	temp = next_token(line, i);
	temp->str = repl_process(temp->str, shell);
	temp_str = strip_quotes(temp->str);
	free(temp->str);
	temp->str = temp_str;
=======

	temp = next_token(line, i);
	temp->str = repl_process(temp->str, shell);
	temp->str = strip_quotes(temp->str);
>>>>>>> 069b946cb7de31e97f7dfd20134dfd76ff5220bd
	return (temp);
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
		token = process_token(line, &i, shell);
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
