/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:46:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/02/05 13:32:24 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	probe_fds(void)
{
	for (int i = 0; i < 256; i++)
	{
		if (read(i, 0, 0) == 0)
			ft_printf_fd(2, "%i ", i);
	}
	ft_printf_fd(2, "\n");
}

int		operator_pipe(t_list *tlist, t_shell *shell)
{
	pid_t		pid;

	shell->args = ((t_ops *)(tlist->content))->args;
	if (pipe(shell->fds) == -1)
		pipe_error(tlist, shell);
	ft_printf_fd(2, "%i %i\n", shell->fds[0], shell->fds[1]);
	pid = fork();
	if (pid < 0)
		pipe_error(tlist, shell);
	if (pid == 0)
	{
		probe_fds();
		close (shell->fds[0]);
		dup2(shell->fds[1], 1);
		shell->rv = shell_execute(shell, shell->args);
		close (shell->fds[1]);
		exit(0);
	}
	wait(0);
	probe_fds();
	close(shell->fds[1]);
//	shell->stdin = dup(0);
	if (dup2(shell->fds[0], 0) == -1)
		return (-1);
	close(shell->fds[0]);
	return (0);
}
