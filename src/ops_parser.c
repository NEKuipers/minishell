/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ops_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 09:58:00 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/13 14:29:30 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
	arr = (char **)malloc(sizeof(char *) * size + 1);
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

char	**parse_args(char *line)
{
	t_list	*list;
	int		i;

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
				i = skip_to_quote(line, i, line[0]);
			ft_lstadd_back(&list, ft_lstnew(ft_substr(line, 0, i + 1)));
			line += i + 1;
			i = -1;
		}
		i++;
	}
	return (list_to_arr(list));
}

static void	clear_ops(void *ops)
{
	char **args;

	free(((t_ops *)ops)->operation);
	args = ((t_ops *)ops)->args;
	while (*args)
	{
		free(*args);
		args++;
	}
	free(args);
	free(ops);
}

t_ops	*set_ops(char *line, int len)
{
	t_ops	*ops;

	ops = (t_ops *)malloc(sizeof(t_ops));
	ops->operation = ft_substr(line, 0, len);
	ops->args = parse_args(ops->operation);
	if (line[len + 1] == '>')
		ops->type = '}';
	else
		ops->type = line[len];
	return (ops);
}

t_list	*parse_ops(char *line)
{
	t_list	*list;
	t_ops	*ops;
	int		i;

	i = 0;
	list = NULL;
	while (1)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i = skip_to_quote(line, i, line[i]);
			if (i == -1)
			{
				ft_lstclear(&list, &clear_ops);
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

int		main(void)
{
	t_list	*list;
	t_list	*tlist;
	int		i;
	char	line[] = "echo abc ; /bin/ls | cat -e | echo abcde";

	list = parse_ops(line);
	tlist = list;
	while (tlist)
	{
		i = 0;
		ft_printf("[%s]\n", ((t_ops *)(tlist->content))->operation);
		while (((t_ops *)(tlist->content))->args[i])
		{
			ft_printf("[[%s]]\n", ((t_ops *)(tlist->content))->args[i]);
			i++;
		}
		ft_putchar_fd(1, '\n');
		tlist = tlist->next;
	}
	while (1) {}
	return (0);
}