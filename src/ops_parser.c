/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ops_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 09:58:00 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/08 12:05:34 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_list	*parse_args(char *line)
{
	t_list	*list;
	int		i;

	i = 0;
	list = NULL;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			
		}
		else if (!line[i] || (line[i] != ' ' && line[i + 1] == ' '))
		{
			ft_lstadd_back(&list, ft_lstnew(ft_substr(line, 0, i)));
			line += i + 1;
			i = 0;
		}
		i++;
	}
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
		if (!line[i] || ft_strchr(";|<>", line[i]))
		{
			ops = (t_ops *)malloc(sizeof(t_ops));
			ops->operation = ft_substr(line, 0, i);
			if (line[i + 1] == '>')
				ops->type = '}';
			else
				ops->type = line[i];
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
	char	line[] = "echo abc ; /bin/ls | cat -e";

	list = parse_ops(line);
	while (list)
	{
		ft_printf("%s ", ((t_ops *)(list->content))->operation);
		ft_printf("%c\n", ((t_ops *)(list->content))->type);
		list = list->next;
	}
	return (0);
}