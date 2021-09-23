/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:46:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/02/10 11:38:22 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		operator_pipe(t_list *tlist, t_shell *shell)
{
	pid_t		pid;

	shell->args = ((t_ops *)(tlist->content))->args;
	if (pipe(shell->fds) == -1)
		pipe_error(tlist, shell);
	pid = fork();
	if (pid < 0)
		pipe_error(tlist, shell);
	if (pid == 0)
	{
		close(shell->fds[0]);
		dupclose_fd(shell->prev_pipe, STDIN_FILENO);
		dup2(shell->fds[1], 1);
		shell->rv = shell_execute(shell, shell->args);
		close (shell->fds[1]);
		exit(0);
	}
	wait(0);
	close(shell->fds[1]);
	shell->prev_pipe = shell->fds[0];
	if (dup2(shell->fds[0], 0) == -1)
		return (-1);
	close(shell->fds[0]);
	return (0);
}