/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_unset.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:16:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/29 12:49:44 by nkuipers      ########   odam.nl         */
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
	if (find_ev(evs, arg) == -1)
		return (evs);
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

static int	valid_identifier(char *command)
{
	int	i;

	i = 0;
	if (ft_strcmp(command, "") == 0)
		return (1);
	if (!ft_isalpha(command[0]) && command[0] != '_')
		return (1);
	while (command[i] != 0)
	{
		if (command[i] > 'z' || command[i] == 96 || \
		(command[i] >= 91 && command[i] <= 94) || \
		(command[i] <= '@' && command[i] <= ':') || command[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int	shell_unset(char **commands, t_shell *shell)
{
	int	i;
	int	rv;

	i = 1;
	rv = 0;
	if (commands[1] == NULL)
	{
		ft_printf("minishell: unset: not enough arguments\n");
		return (1);
	}
	while (commands[i] != NULL)
	{
		if (valid_identifier(commands[i]) == 1)
			rv = 1;
		else
			shell->evs = remove_env(shell->evs, commands[i]);
		i++;
	}
	if (rv == 1)
		ft_printf("minishell: unset: `': not a valid identifier\n");
	return (rv);
}
