/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:15:06 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/14 16:51:21 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Export: if no argument is supplied, all environment variables are printed
** in alphabetical order.
** If an argument with an = is supplied, such as TEST=NEW, a new environment
** variable is added following that scheme.
** If a different argument is supplied (i.e. export test), a new environment
** variable is added with no value (test='').
*/

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
			if (ft_strncmp(n[i], n[j], (ft_strlen(n[i]) > ft_strlen(n[j])
						? ft_strlen(n[i]) : ft_strlen(n[j]))) > 0)
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

static int	match_env(char **evs, char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (evs[i])
	{
		j = 0;
		while (evs[i][j] != '=')
			j++;
		if (ft_strncmp(evs[i], arg, j) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	replace_env(char **evs, char *arg, int index)
{
	if (ft_strchr(arg, '='))
	{
		free(evs[index]);
		evs[index] = ft_strdup(arg);
	}
}

int	shell_export(char **commands, t_shell *shell)
{
	char	**temp[2];
	int		i;
	int		index;

	i = 1;
	while (commands[i] != NULL)
	{
		index = match_env(shell->evs, commands[i]);
		if (index >= 0)
			replace_env(shell->evs, commands[i], index);
		else
			shell->evs = set_new_env(shell->evs, commands[i]);
		i++;
	}
	if (commands[1] == NULL)
	{
		temp[0] = sort_alpha(shell->evs);
		temp[1] = shell->evs;
		shell->evs = temp[0];
		shell_env(shell);
		shell->evs = temp[1];
		free_array(temp[0]);
	}
	return (0);
}
