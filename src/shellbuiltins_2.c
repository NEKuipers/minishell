/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 10:05:56 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/22 13:50:12 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** This is echo. It prints all arguments back with one space in between and a
** nline at the end, except for when the -n flag is given.
*/

int		shell_echo(char **args, char **evs)
{
	int i;
	int	nflag;

	i = 1;
	nflag = 0;
	(void)evs;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-n", 3) == 0)
		{
			i++;
			nflag = 1;
		}
		if (args[i] == NULL)
			return (0);
		else if (args[i + 1] == NULL && nflag == 0)
			ft_printf("%s\n", args[i]);
		else if (args[i + 1] == NULL)
			ft_printf("%s", args[i]);
		else
			ft_printf("%s ", args[i]);
		i++;
	}
	return (0);
}

/*
** Free the malloced stuff and exit.
*/

int		shell_exit(char **args, char **evs)
{
	free_args(evs);
	free_args(args);
	exit(0);
	return (0);
}
