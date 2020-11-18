/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fds.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 14:21:03 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/11/18 14:30:15 by nkuipers      ########   odam.nl         */
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
	dup2(shell->in, 0);
	dup2(shell->out, 1);
}
