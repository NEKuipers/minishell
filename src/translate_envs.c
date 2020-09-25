/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translate_envs.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 16:04:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/25 17:02:09 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Environment variables called in the terminal should translate to their value.
** These functions check if any argument begins with $ and if there is an 
** environment variable called, will then translate it to the corresponding 
** value.
**
** Example: environment variable $USER=nkuipers;
** 'echo $USER' prints 'nkuipers' to the terminal.
*/

static char	*swap_env(char *arg, char **evs)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (evs[i])
	{
		j = 0;
		if (ft_strncmp(evs[i], &arg[1], ft_strlen(&arg[1])) == 0)
		{
			while (evs[i][j] != '=')
				j++;
			j++;
			temp = arg;
			arg = ft_strdup(&evs[i][j]);
			free(temp);
		}
		i++;
	}
	return (arg);
}

char		**transl_env(char **args, char **evs)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1] != '?')
			args[i] = swap_env(args[i], evs);
		i++;
	}
	return (args);
}
