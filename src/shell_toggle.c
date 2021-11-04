/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_toggle.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 13:05:57 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/04 14:56:35 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	shell_toggle_bold(char **commands)
{
	if (commands[3] != NULL)
		ft_printf("error: too many arguments\n");
	if (commands[2] == NULL)
		ft_printf("\x1b[37;01m");
	else if (ft_strcmp(commands[2], "black") == 0)
		ft_printf("\x1b[30;01m");
	else if (ft_strcmp(commands[2], "red") == 0)
		ft_printf("\x1b[31;01m");
	else if (ft_strcmp(commands[2], "green") == 0)
		ft_printf("\x1b[32;01m");
	else if (ft_strcmp(commands[2], "yellow") == 0)
		ft_printf("\x1b[33;01m");
	else if (ft_strcmp(commands[2], "blue") == 0)
		ft_printf("\x1b[34;01m");
	else if (ft_strcmp(commands[2], "purple") == 0)
		ft_printf("\x1b[35;01m");
	else if (ft_strcmp(commands[2], "cyan") == 0)
		ft_printf("\x1b[36;01m");
	else if (ft_strcmp(commands[2], "white") == 0)
		ft_printf("\x1b[37;01m");
	else
		ft_printf("error: enter a valid color\n");
	return (0);
}

int	shell_toggle(char **commands)
{
	if (commands[1] == NULL)
		ft_printf("error: select a color\n");
	else if (ft_strcmp(commands[1], "bold") == 0)
		return (shell_toggle_bold(commands));
	else if (commands[2] != NULL)
		ft_printf("error: too many arguments\n");
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
