/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translate_envs.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 16:04:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/01 13:25:58 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Environment variables called in the terminal should translate to their value.
** These functions check if any argument begins with $ and if there is an
** environment variable called, will then translate it to the corresponding
** value.
**
** Example: environment variable $USER=nkuipers;
** 'echo $USER' prints 'nkuipers' to the terminal.
*/

char		*insert_rv(char *rv, char *arg)
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

size_t		ft_evlen(char *ev)
{
	int		i;

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
		if (ft_strncmp(evs[i], &arg[1], ft_strlen(&arg[1])) == 0
			&& ft_strlen(&arg[1]) == ft_evlen((evs[i])))
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

char		**transl_env(t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	while (shell->args[i])
	{
		if (shell->args[i][0] == '$' && shell->args[i][1] != '?')
			shell->args[i] = swap_env(shell->args[i], shell->evs);
		j = 0;
		while (shell->args[i][j])
		{
			if (shell->args[i][j] == '?' && j > 0)
				if (shell->args[i][j - 1] == '$')
				{
					shell->args[i] = insert_rv(ft_itoa(shell->rv),
						shell->args[i]);
					j = 0;
				}
			j++;
		}
		i++;
	}
	return (shell->args);
}
