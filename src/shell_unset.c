/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_unset.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:16:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/28 09:38:05 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell_env(t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	while (shell->evs[i])
	{
		j = 0;
		while (shell->evs[i][j + 1] != '\0')
			j++;
		if (shell->evs[i][j] != '=')
			ft_printf("%s\n", shell->evs[i]);
		i++;
	}
	return (0);
}

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
	ret[i - 1] = NULL;
	replace_array(ret, evs, arg);
	free_array(evs);
	return (ret);
}

int	shell_unset(char **commands, t_shell *shell)
{
	int	i;

	i = 1;
	if (commands[1] == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	while (commands[i] != NULL)
	{
		if (ft_strcmp(commands[i], "") != 0)
			shell->evs = remove_env(shell->evs, commands[i]);
		i++;
	}
	return (0);
}
