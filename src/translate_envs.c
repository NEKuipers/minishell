/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translate_envs.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 16:04:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/13 15:57:04 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*insert_rv(char *rv, char *arg)
{
	int		i;
	int		j;
	char	*new;
	char	*temp;

	i = 0;
	new = (char *)malloc(sizeof(ft_strlen(arg)));
	while (!(arg[i] == '$' && arg[i + 1] == '?'))
		i++;
	j = -1;
	while (j++ < i - 1)
		new[j] = arg[j];
	temp = new;
	new = ft_strjoin(new, rv);
	free(temp);
	free(rv);
	i += 2;
	if (arg[i] != '\0')
	{
		temp = new;
		new = ft_strjoin(new, &arg[i]);
		free(temp);
	}
	free(arg);
	return (new);
}

size_t	ft_evlen(char *ev)
{
	int	i;

	i = 0;
	while (ev[i] != '=')
		i++;
	return (i);
}

static char	*swap_env(char *arg, char **evs)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (evs[i])
	{
		j = 0;
		if (ft_strncmp(evs[i], &arg[1], ft_evlen(evs[i])) == 0)
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

static int	escapecheck(char *arg, int dollar)
{
	if (dollar == 0)
		return (0);
	if (ft_strncmp(&arg[dollar - 1], "\\$", 2) == 0)
		return (1);
	return (0);
}

static char	*remove_backslash(char *arg)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(ft_strlen(arg)));
	if (new == NULL)
		return (NULL);
	while (arg[i])
	{
		if (!(arg[i] == '\\' && arg[i + 1] == '$'))
		{
			new[j] = arg[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(arg);
	return (new);
}

static char	*choose_expansion(char **args, t_shell *shell, int i, int j)
{
	if (args[i][j + 1] == '?')
		return (insert_rv(ft_itoa(shell->rv), args[i]));
	else
		return (swap_env(args[i], shell->evs));
}

char	**expand_commands(t_shell *shell, char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$')
			{
				if (escapecheck(args[i], j) == 1)
					args[i] = remove_backslash(args[i]);
				else
				{
					args[i] = choose_expansion(args, shell, i, j);
					j = 0;
				}
			}
			j++;
		}
		i++;
	}
	return (args);
}
