/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 10:05:56 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 10:13:49 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		shell_echo(char **args, char **evs)
{
	int i;

	i = 1;

	(void)evs;
	while (args[i])
	{
		if (args[i + 1] == NULL)
			ft_printf("%s\n", args[i]);
		else
			ft_printf("%s ", args[i]);
		i++;
	}
	return (0);
}
