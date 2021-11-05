/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_export_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 17:04:33 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/29 17:04:52 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**sort_alpha(char **evs)
{
	char	**n;
	char	*temp;
	int		i;
	int		j;

	n = copy_evs(evs);
	i = 0;
	j = 2;
	while (n[i] != NULL && i < j - 1)
	{
		j = i + 1;
		while (n[j] != NULL)
		{
			if (ft_strncmp(n[i], n[j], max(ft_strlen(n[i]), \
				ft_strlen(n[j]))) > 0)
			{
				temp = n[i];
				n[i] = n[j];
				n[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (n);
}

int	match_env(char **evs, char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (evs[i])
	{
		j = 0;
		while (evs[i][j] != '=')
			j++;
		if (evs[i][j - 1] == '+')
			j--;
		if (ft_strncmp(evs[i], arg, j) == 0)
			return (i);
		i++;
	}
	return (-1);
}
