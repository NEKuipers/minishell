/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fds.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 14:21:03 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/09/24 13:38:54 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std_fds(t_shell *shell)
{
	dup2(shell->fds[0], 0);
	dup2(shell->fds[1], 1);
	dup2(shell->stdinp, 0);
	dup2(shell->stdout, 1);
}

void	dupclose_fd(int fd, int sec_fd)
{
	if (fd != sec_fd)
	{
		dup2(fd, sec_fd);
		close(fd);
	}
}

void	dup_and_close_pipe(int pipe[2], int dupped)
{
	dup2(pipe[dupped], dupped);
	close(pipe[0]);
	close(pipe[1]);
}
