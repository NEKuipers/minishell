/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fds.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 14:21:03 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/01/10 14:20:56 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_close_fd(int fd)
{
    if (fd > 0)
        close(fd);
}

void	reset_std_fds(t_shell *shell)
{
	dup2(shell->fds[0], 0);
	dup2(shell->fds[1], 1);
}
