/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 12:05:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/15 11:22:49 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_int_handler(int code)
{
	(void)code;
	if (g_signal.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
		g_signal.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		rl_replace_line("", 0);
		g_signal.exit_status = 130;
	}
	g_signal.sigint = 1;
	g_signal.cht = 0;
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

void	signal_dummy(int code)
{
	(void)code;
	return ;
}

int	dummy(void)
{
	return (0);
}

void	init_signal(void)
{
	struct sigaction	sig;

	g_signal.sigint = 0;
	g_signal.sigquit = 0;
	g_signal.pid = 0;
	g_signal.exit_status = 0;
	g_signal.cht = 0;
	sig.__sigaction_u.__sa_handler = signal_int_handler;
	rl_event_hook = dummy;
	sig.sa_mask = 0;
	sig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig, NULL);
}
