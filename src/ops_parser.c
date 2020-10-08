/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ops_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 09:58:00 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/08 14:50:36 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_list	*parse_args(char *line)
{
	t_list	*list;
	int		i;
	char	*cptr;

	i = 0;
	list = NULL;
	while (line[i])
	{
		while (*line == ' ')
			line++;
		if (line[0] == '\"' || line[0] == '\'')
		{
			cptr = ft_strchr(line + 1, line[0]);
			ft_printf("%p\n", cptr);
			ft_lstadd_back(&list, ft_lstnew(ft_substr(line + 1, 0, line - cptr)));
			line = cptr + 1;
			i = -1;
		}
		else if (!line[i + 1] || (line[i] != ' ' && line[i + 1] == ' '))
		{
			ft_lstadd_back(&list, ft_lstnew(ft_substr(line, 0, i + 1)));
			line += i + 1;
			i = -1;
		}
		i++;
	}
	while (list)
	{
		ft_printf("  |%s\n", (char *)(list->content));
		list = list->next;
	}
	return (list);
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
	char	line[] = "echo \"abc ; /bin/ls | cat -e\"";

	list = parse_ops(line);
	while (list)
	{
		ft_printf("%s\n", ((t_ops *)(list->content))->operation);
		parse_args(((t_ops *)(list->content))->operation);
		ft_putchar_fd(1, '\n');
		list = list->next;
	}
	return (0);
}