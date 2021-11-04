/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_unset.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:16:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/04 12:19:09 by bmans         ########   odam.nl         */
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

int	valid_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd, "") == 0)
		return (1);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (1);
	while (cmd[i] != 0 && cmd[i] != '=')
	{
		if (cmd[i] < 32 || cmd[i] > 122 || cmd[i] == ':' || cmd[i] == ';' \
			|| cmd[i] == '<' || cmd[i] == 96 || (cmd[i] < 95 && cmd[i] > 90) \
				 || cmd[i] == '?' || cmd[i] == '@' || cmd[i] == '>')
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
		{
			ft_printf("minishell: unset: `%s': not a valid identifier\n", \
				commands[i]);
			rv = 1;
		}
		else
			shell->evs = remove_env(shell->evs, commands[i]);
		i++;
	}
	return (rv);
}
