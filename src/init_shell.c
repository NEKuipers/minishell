/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_shell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 16:16:31 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/22 16:17:23 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_evs(char **inputs)
{
	int		i;
	char	**ret;

	i = 0;
	while (inputs[i])
		i++;
	ret = malloc((i + 1) * (sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (inputs[i])
	{
		ret[i] = ft_strdup(inputs[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static void	levelup_shell(t_shell *shell)
{
	char	**commands;
	char	*temp;
	char	*levelstring;
	int		lvl;

	commands = (char **)malloc(sizeof(char *) * 3);
	commands[0] = ft_strdup("export");
	lvl = ft_atoi(getenv("SHLVL"));
	lvl += 1;
	levelstring = ft_itoa(lvl);
	temp = ft_strjoin("SHLVL=", levelstring);
	free(levelstring);
	commands[1] = ft_strdup(temp);
	free(temp);
	commands[2] = NULL;
	shell_export(commands, shell);
	free_array(commands);
}

void	init_shell_values(t_shell *shell, char **envp)
{
	shell->evs = copy_evs(envp);
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	shell->exit = 0;
	shell->rv = 0;
	shell->no_exec = 0;
	reset_fds(shell);
	levelup_shell(shell);
}
