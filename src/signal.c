/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 12:05:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/28 14:29:56 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_int_handler(int code)
{
	(void)code;
	if (g_signal.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		g_signal.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_signal.exit_status = 130;
	}
	ft_putstr_fd("\b\b<$ ", STDERR);
	g_signal.sigint = 1;
}

void	signal_quit_handler(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_signal.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		g_signal.exit_status = 131;
		g_signal.sigquit = 1;
	}
	ft_memdel(nbr);
}

void	init_signal(void)
{
	g_signal.sigint = 0;
	g_signal.sigquit = 0;
	g_signal.pid = 0;
	g_signal.exit_status = 0;
}
