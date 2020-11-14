/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_inputstring.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 14:18:35 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/11/14 10:54:45 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**list_to_arr(t_list *list)
{
	int		size;
	int		i;
	t_list	*lst;
	char	**arr;

	if (!list)
		return (NULL);
	lst = list;
	size = ft_lstsize(list);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		arr[i] = ft_strdup(lst->content);
		i++;
		lst = lst->next;
	}
	arr[size] = NULL;
	ft_lstclear(&list, &free);
	return (arr);
}

static int	skip_to_quote(char *line, int index, char type)
{
	while (1)
	{
		index++;
		if (!line[index])
			return (-1);
		if (line[index] == type)
			return (index);
	}
}

char	**parse_args(char *line, t_ops *ops)
{
	t_list	*list;
	int		i;

	ops->in_quotes = 0;
	i = 0;
	list = NULL;
	while (line[i])
	{
		while (*line == ' ')
			line++;
		if (!line[0])
			break ;
		if ((line[0] == '\"' || line[0] == '\'' || \
			!line[i + 1] || (line[i] != ' ' && line[i + 1] == ' ')) && i > 0)
		{
			if (line[0] == '\"' || line[0] == '\'')
			{
				i = skip_to_quote(line, i, line[0]);
				ops->in_quotes = 1;
			}
			if (ops->in_quotes == 0)
				ft_lstadd_back(&list, ft_lstnew(ft_substr(line, 0, i + 1)));
			else
				ft_lstadd_back(&list, ft_lstnew(ft_substr(line, 1, i - 1)));
			line += i + 1;
			i = -1;
		}
		i++;
	}
	return (list_to_arr(list));
}

static void	clear_ops(void *ops)
{
	free(((t_ops *)ops)->operation);
	free_args(((t_ops *)ops)->args);
	free(ops);
}

t_ops	*set_ops(char *line, int len)
{
	t_ops		*ops;
	static int	i;

	i = 0;
	ops = (t_ops *)malloc(sizeof(t_ops));
	ops->operation = ft_substr(line, 0, len);
	ops->args = parse_args(ops->operation, ops);
	if (line[len] && line[len + 1] == '>')
		ops->type[i] = '}';
	else
		ops->type[i] = line[len];
	i++;
	return (ops);
}

t_list	*parse_ops(char *line)
{
	t_list	*list;
	t_ops	*ops;
	int		i;

	i = 0;
	list = NULL;
	if (!line[i])
		return (NULL);
	while (1)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i = skip_to_quote(line, i, line[i]);
			if (i == -1)
			{
				ft_lstclear(&list, &clear_ops);
				ft_printf("error: syntax\n");
				return (NULL);
			}
		}
		else if (!line[i] || ft_strchr(";|<>", line[i]))
		{
			ops = set_ops(line, i);
			ft_lstadd_back(&list, ft_lstnew(ops));
			if (!line[i])
				return (list);
			line += i + 1;
			i = 0;
		}
		i++;
	}
}

int		parse_inputstring(t_shell *shell, char *input)
{
	t_list	*list;
	t_list	*tlist;
	t_list	*temp;
	int		i;

	i = 0;
	list = parse_ops(input);
	if (!list)
		return (0);
	tlist = list;
	free(input);
	shell->ops = list;
	while (tlist)
	{
		if (((t_ops *)(tlist->content))->type[i] == '|')
		{
			shell->rv = shell_execute(shell, ((t_ops *)(tlist->content))->args);
			i++;
		}
		else
			shell->rv = shell_execute(shell, ((t_ops *)(tlist->content))->args);
		free_args(((t_ops *)(tlist->content))->args);
		temp = tlist;
		free((t_ops *)(tlist->content));
		tlist = tlist->next;
	}
	ft_lstclear(&list, &clear_ops);
	return (0);
}
