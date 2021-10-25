/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fds.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 11:02:03 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/22 16:39:44 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_shell *shell)
{
	dup2(shell->in, STDIN);
	dup2(shell->out, STDOUT);
}

void	close_fds(t_shell *shell)
{
	ft_close(shell->fdin);
	ft_close(shell->fdout);
	ft_close(shell->pipin);
	ft_close(shell->pipout);
}

void	reset_fds(t_shell *shell)
{
	shell->fdin = -1;
	shell->fdout = -1;
	shell->pipin = -1;
	shell->pipout = -1;
	shell->pid = -1;
}

void	full_fd_reset(t_shell *shell)
{
	reset_std(shell);
	close_fds(shell);
	reset_fds(shell);
}
