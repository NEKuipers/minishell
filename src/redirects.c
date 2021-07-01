/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 12:26:13 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/07/01 12:59:43 by nkuipers      ########   odam.nl         */
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
	// pid_t pid;
	// int	i;
	(void)tlist;
	(void)pipeline;

	shell->rv = shell_execute(shell, shell->args);
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
	if (((t_ops *)(tlist->content))->type > ';')
	{
		operator_exec(tlist, shell, &pipeline);
		if (((t_ops *)(tlist->content))->type != '|')
			tlist = tlist->next;
	}
	while (shell->count > 0)
	{
		shell->args = ((t_ops *)(tlist->content))->args;
		shell->rv = shell_execute(shell, shell->args);
		tlist = tlist->next;
		shell->count = ft_lstsize(tlist);
	}
	return (0);
}
