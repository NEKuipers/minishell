/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translate_envs.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 16:04:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 16:22:20 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*swap_env(char *arg, char **evs)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = ft_strlen(&arg[1]);
	while (evs[i])
	{
		j = 0;
		if (ft_strncmp(evs[i], arg, k) == 0)
		{
			while (evs[i][j - 1] != '=')
				j++;
			arg = ft_strdup(&evs[i][j]);
		}
		i++;
	}
	return (arg);
}

char		**transl_env(char **args, char **evs)
{
	int		i;
	char	*temp;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1] != '?')
		{
			temp = args[i];
			args[i] = swap_env(args[i], evs);
			free(temp);
		}
		i++;
	}
	return (args);
}
