/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fds.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 14:21:03 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/02/05 14:08:10 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_close_fd(int fd)
{
    if (fd > 0)
        close(fd);
}

void	init_std_fds(t_shell *shell)
{
	shell->fds[0] = -1;
	shell->fds[1] = -1;
	shell->stdin = dup(0);
	shell->stdout = dup(1);
	ft_printf_fd(2, "%i %i %i %i\n", shell->fds[0], shell->fds[1], shell->stdin, shell->stdout);
}

void	reset_std_fds(t_shell *shell)
{
    dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
//	dup2(shell->fds[0], 0);
//	dup2(shell->fds[1], 1);
}
