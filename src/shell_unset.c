/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_unset.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:16:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/02 11:20:05 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Unset removes an environment variable from the list.
*/

char	**remove_env(char **evs, char *arg)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	while (evs[i])
		i++;
	ret = malloc((i) * (sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (evs[i])
	{
		j = 0;
		while (evs[i][j] != '=')
			j++;
		if (ft_strncmp(evs[i], arg, j - 1) != 0)
			ret[i] = ft_strdup(evs[i]);
		i++;
	}
	ret[i] = NULL;
	free_args(evs);
	return (ret);
}

int		shell_unset(char **args, char ***evs)
{
	int		i;

	i = 1;
	if (args[1] == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	while (args[i] != NULL)
	{
		*evs = remove_env(*evs, args[i]);
		i++;
	}
	return (0);
}
