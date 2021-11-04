/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 12:05:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/04 15:55:54 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	stop_heredoc()
{
	int	fds[2];

}
*/

void	signal_int_handler(int code)
{
	if (g_signal.shlvl == 1)
		return ;
	(void)code;
	if (g_signal.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		rl_replace_line("", 0);
		if (g_signal.cht == 0)
			ft_putstr_fd("<$ ", STDERR);
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

void	init_signal(void)
{
	struct sigaction	sig;

	g_signal.sigint = 0;
	g_signal.sigquit = 0;
	g_signal.pid = 0;
	g_signal.exit_status = 0;
	g_signal.cht = 0;
	sig.__sigaction_u.__sa_handler = signal_int_handler;
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
}
