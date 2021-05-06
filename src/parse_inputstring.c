/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_inputstring.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 14:18:35 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/05/06 16:18:54 by nkuipers      ########   odam.nl         */
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
	while (line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
		while (*line == ' ')
			line++;
		if (!line[0])
			break ;
		if ((line[0] == '\"' || line[0] == '\'' || !line[i + 1] || (line[i] != ' ' && line[i + 1] == ' ')) && i > 0)
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
			if (line[i] == '\0')
				break;
			line += 1 + i;
			i = -1;
		}
		i++;
	}
	return (list_to_arr(list));
}

t_ops	*set_ops(char *line, int len)
{
	t_ops		*ops;

	ops = (t_ops *)malloc(sizeof(t_ops));
	ops->operation = ft_substr(line, 0, len);
	ops->args = parse_args(ops->operation, ops);
	if (line[len] && line[len + 1] == '>')
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
			line += (line[i] && line[i + 1] == '>' ?  1 : 0);
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

	list = parse_ops(input);
	if (!list)
		return (0);
	tlist = list;
	free(input);
	shell->ops = list;
	// shell->prev_pipe = STDIN_FILENO;
	shell->count = ft_lstsize(tlist);
	run_cmds(shell, tlist);
	reset_std_fds(shell);
	ft_lstclear(&list, &clear_ops);
	return (0);
}

static int	count_pipes(t_list *tlist)
{
	int		count;
	t_list	*temp;

	temp = tlist;
	count = 0;
	while (temp && ((t_ops *)(temp->content))->type == '|')
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int		set_pipes(t_pipeline *pipeline, t_shell *shell, t_list *tlist)
{
	int i;
	int	count;
	
	i = 0;
	count = pipeline->amount;
	pipeline->pipes = (int *)malloc(sizeof(int) * pipeline->amount + 1);
	if (!pipeline->pipes)
		pipe_error(tlist, shell);
	while (count > 0)
	{
		if (pipe(pipeline->pipes + i * 2) < 0)
			pipe_error(tlist, shell);
		i += 2;
		count--;
	}
	return (0);
}

int		run_cmds(t_shell *shell, t_list *tlist)
{
	t_pipeline	pipeline;

	pipeline.amount = count_pipes(tlist);
	pipeline.pipecount = 0;
	if (pipeline.amount > 0)
		set_pipes(&pipeline, shell, tlist);
	// for (int i = 0; pipeline.pipes[i]; i++)
	// 	ft_printf("filedescriptor pipe %d is %d\n", i, pipeline.pipes[i]);
	while (shell->count > 1)
	{
		shell->stdin = dup(0);
		shell->args = ((t_ops *)(tlist->content))->args;
		if (((t_ops *)(tlist->content))->type > ';')
		{
			// dupclose_fd(shell->prev_pipe, STDIN_FILENO);
			operator_exec(tlist, shell, &pipeline);
			if (((t_ops *)(tlist->content))->type != '|')
				tlist = tlist->next;
		}
		else
			shell->rv = shell_execute(shell, shell->args);
		tlist = tlist->next;
		shell->count = ft_lstsize(tlist);
		pipeline.pipecount += 2;
	}
	if (tlist)
	{
		shell->args = ((t_ops *)(tlist->content))->args;
		// dupclose_fd(shell->prev_pipe, STDIN_FILENO);
		shell->rv = shell_execute(shell, shell->args);
		dup2(shell->stdin, STDIN_FILENO);
	}
	// if (pipeline.pipes)
	// 	free(pipeline.pipes);
	return (0);
}
