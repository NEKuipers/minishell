/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_toggle.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 13:05:57 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/04 13:18:36 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell_toggle(char **commands, t_shell *shell)
{
	(void)shell;
	if (commands[2] != NULL)
		ft_printf("error: too many arguments\n");
	if (commands[1] == NULL)
		ft_printf("error: select a color\n");
	else if (ft_strcmp(commands[1], "black") == 0)
		ft_printf("\033[0;30m");
	else if (ft_strcmp(commands[1], "red") == 0)
		ft_printf("\033[0;31m");
	else if (ft_strcmp(commands[1], "green") == 0)
		ft_printf("\033[0;32m");
	else if (ft_strcmp(commands[1], "yellow") == 0)
		ft_printf("\033[0;33m");
	else if (ft_strcmp(commands[1], "blue") == 0)
		ft_printf("\033[0;34m");
	else if (ft_strcmp(commands[1], "purple") == 0)
		ft_printf("\033[0;35m");
	else if (ft_strcmp(commands[1], "cyan") == 0)
		ft_printf("\033[0;36m");
	else if (ft_strcmp(commands[1], "white") == 0)
		ft_printf("\033[0;37m");
	else
		ft_printf("error: enter a valid color\n");
	return (0);
}
