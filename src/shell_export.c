/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:15:06 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/07 16:00:03 by nkuipers      ########   odam.nl         */
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

char		**sort_alpha(char **evs)
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

char		**set_new_env(char **evs, char *arg)
{
	int		i;
	char	**ret;

	i = 0;
	while (evs[i])
		i++;
	ret = malloc((i + 2) * (sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (evs[i])
	{
		ret[i] = ft_strdup(evs[i]);
		i++;
	}
	ret[i] = ft_strdup(arg);
	i++;
	ret[i] = NULL;
	free_args(evs);
	return (ret);
}

static int	match_env(char **evs, char *arg)
{
	int		i;
	int		j;

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

int			shell_export(t_shell *shell)
{
	char	**temp[2];
	int		i;
	int		index;

	i = 1;
	while (shell->args[i] != NULL)
	{
		index = match_env(shell->evs, shell->args[i]);
		if (index >= 0)
			replace_env(shell->evs, shell->args[i], index);
		else
			shell->evs = set_new_env(shell->evs, shell->args[i]);
		i++;
	}
	if (shell->args[1] == NULL)
	{
		temp[0] = sort_alpha(shell->evs);
		temp[1] = shell->evs;
		shell->evs = temp[0];
		shell_env(shell);
		shell->evs = temp[1];
		free_args(temp[0]);
	}
	return (0);
}
