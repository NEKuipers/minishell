/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/23 11:20:24 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_loop(char **envp)
{
	ft_printf(">");
	(void)envp;

}

int		main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
	{
		ft_printf("%s\n", &envp[21][4]);
		shell_loop(envp);
	}
	return (0);
}
