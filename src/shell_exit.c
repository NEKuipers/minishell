/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:05:42 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/05 16:05:57 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_exit(t_shell *shell, char **commands)
{
	shell->exit = 1;
	if (commands[1] && ft_strisnum(commands[1]) == 0)
	{
		shell->rv = 255;
		ft_printf_fd(2, "exit\nminishell:");
		ft_printf_fd(2, "exit: %s: numeric argument required\n", commands[1]);
	}
	else if (commands[1] && commands[2])
	{
		shell->rv = 1;
		shell->exit = 0;
		ft_printf_fd(STDERR, "exit\nminishell: exit: too many arguments\n");
	}
	else
	{
		if (commands[1])
			shell->rv = ft_atoi(commands[1]);
		else
			shell->rv = 0;
		ft_printf_fd(0, "exit\n");
	}
}
