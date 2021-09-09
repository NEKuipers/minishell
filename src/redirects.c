/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 12:26:13 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/09/09 13:25:11 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	operator_redirect_output(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;

	shell->fds[0] = dup(STDOUT_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDOUT_FILENO);
	close(fd);
	return (0);
}

int	operator_append_output(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;

	shell->fds[0] = dup(STDOUT_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDOUT_FILENO);
	close(fd);
	return (0);
}

int	operator_redirect_input(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;

	shell->fds[0] = dup(STDIN_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "%s: no such file or directory\n", filename);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDIN_FILENO);
	close(fd);
	return (0);
}

int	operator_pipe(t_list *tlist, t_shell *shell, t_pipeline *pipeline)
{
	int	fds[pipeline->amount];
	int i;
	int cmdcount;

	i = 0;
	while (i < pipeline->amount)
	{
		if (pipe(fds + i * 2) < 0)
			return (-1);
		i++;
	}
	cmdcount = 0;
	while (((t_ops *)(tlist->content))->type == '|')
	{
		pipeline->pid = fork();
		if (pipeline->pid == 0)
		{
			if (cmdcount != 0)
				if (dup2(fds[(cmdcount - 1) * 2], 0) < 0)
					return (-1);
			if (cmdcount != pipeline->amount)
				if (dup2(fds[(cmdcount * 2 + 1)], 1) < 0)
					return (-1);
			for (int j = 0; j < 2 * pipeline->amount; j++)
                close(fds[j]);
			shell->rv = shell_execute(shell, shell->args);
		}
		else if (pipeline->pid < 0)
			return (-1);
		tlist = tlist->next;
		cmdcount++;
	}
	return (0);
}

int	operator_exec(t_list *tlist, t_shell *shell, t_pipeline *pipeline)
{
	shell->args = ((t_ops *)(tlist->content))->args;
	if (((t_ops *)(tlist->content))->type == '|')
		return (operator_pipe(tlist, shell, pipeline));
	else if (((t_ops *)(tlist->content))->type == '>')
		return (operator_redirect_output(tlist, shell));
	else if (((t_ops *)(tlist->content))->type == '}')
		return (operator_append_output(tlist, shell));
	else if (((t_ops *)(tlist->content))->type == '<')
		return (operator_redirect_input(tlist, shell));
	else
		return (-1);
}

static void	count_pipes(t_list *tlist, t_pipeline *pipeline)
{
	pipeline->amount = 1;
	while (tlist->next != NULL)
	{
		tlist = tlist->next;
		if (((t_ops *)(tlist->content))->type != '|')
			break;
		pipeline->amount += 1;
	}
	return ;
}

int		run_cmds(t_shell *shell, t_list *tlist)
{
	t_pipeline pipeline;

	pipeline.amount = 0;
	if (((t_ops *)(tlist->content))->type == '|')
		count_pipes(tlist, &pipeline);
	while (shell->count > 0)
	{
		shell->args = ((t_ops *)(tlist->content))->args;
		if (((t_ops *)(tlist->content))->type > ';')
		{
			operator_exec(tlist, shell, &pipeline);
			if (((t_ops *)(tlist->content))->type != '|')
				tlist = tlist->next;
		}
		else
			shell->rv = shell_execute(shell, shell->args);
		tlist = tlist->next;
		shell->count = ft_lstsize(tlist);
	}
	return (0);
}
