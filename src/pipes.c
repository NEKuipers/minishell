/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:46:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/09/24 16:17:14 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	operator_pipe(t_list *tlist, t_shell *shell)
{
	pid_t	pid;

	shell->args = ((t_ops *)(tlist->content))->args;
	if (pipe(((t_ops *)(tlist->content))->fds) == -1)
		pipe_error(tlist, shell);
	pid = fork();
	if (pid < 0)
		pipe_error(tlist, shell);
	if (pid == 0)
	{
		close(((t_ops *)(tlist->content))->fds[0]);
		dup2(shell->prev_pipe, STDIN_FILENO);
		dup2(((t_ops *)(tlist->content))->fds[1], 1);
		shell->rv = shell_execute(shell, shell->args);
		exit(0);
	}
	wait(NULL);
	close(((t_ops *)(tlist->content))->fds[1]);
	shell->prev_pipe = ((t_ops *)(tlist->content))->fds[0];
	return (0);
}
