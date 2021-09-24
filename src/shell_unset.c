/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_unset.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:16:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/09/24 09:23:53 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Unset removes an environment variable from the list.
*/

static void	replace_array(char **ret, char **evs, char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (*evs)
	{
		j = 0;
		while ((*evs)[j] != '=')
			j++;
		if (ft_strncmp(*evs, arg, j + 1) != '=')
		{
			ret[i] = ft_strdup(*evs);
			i++;
		}
		evs++;
	}
	ret[i] = NULL;
}

char	**remove_env(char **evs, char *arg)
{
	int		i;
	char	**ret;

	i = 0;
	while (evs[i])
		i++;
	ret = malloc(i * (sizeof(char *)));
	if (!ret)
		return (NULL);
	replace_array(ret, evs, arg);
	free_args(evs);
	return (ret);
}

int	shell_unset(t_shell *shell)
{
	int	i;

	i = 1;
	if (shell->args[1] == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	while (shell->args[i] != NULL)
	{
		shell->evs = remove_env(shell->evs, shell->args[i]);
		i++;
	}
	return (0);
}
