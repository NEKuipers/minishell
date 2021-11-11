/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec_bin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 11:36:39 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/11 12:53:40 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	pid_error(char **paths, char **args)
{
	free_array(args);
	free_array(paths);
	exit(127);
}

static void	shell_execpath_3(char **paths, char **args, char **evs)
{
	char		*temp;
	int			i;
	struct stat	buf;

	i = 0;
	while (paths[i])
	{
		if (stat(paths[i], &buf) == 0)
		{
			temp = ft_strdup(paths[i]);
			execve(temp, args, evs);
		}
		i++;
	}
}

static int	shell_execpath_2(char **paths, char **args, \
	char **evs, t_token *token)
{
	int	rv;

	if (ft_strcmp(args[0], "./minishell") == 0)
		signal(SIGINT, &signal_dummy);
	if (ft_strncmp(args[0], "./", 2) == 0)
		paths = set_new_env(paths, args[0], 1);
	g_signal.pid = fork();
	if (g_signal.pid == 0)
	{
		shell_execpath_3(paths, args, evs);
		ft_printf("minishell: command not found: %s.\n", args[0]);
		free_tokens(token);
		pid_error(paths, args);
	}
	waitpid(g_signal.pid, &rv, 0);
	free_array(paths);
	if (g_signal.sigint == 1 || g_signal.sigquit == 1)
		return (g_signal.exit_status);
	return (WEXITSTATUS(rv));
}

int	execute_bin(char **commands, t_shell *shell, t_token *token)
{
	char	**paths;
	int		i;
	char	*temp;
	char	*newpath;

	newpath = ft_strjoin("/", commands[0]);
	i = find_ev(shell->evs, "PATH=");
	if (i == -1)
		paths = paths_without_path(commands);
	else
	{
		paths = ft_split(&((shell->evs)[i][5]), ':');
		i = 0;
		paths = set_new_env(paths, "/", 0);
		while (paths[i])
		{
			temp = paths[i];
			paths[i] = ft_strjoin(paths[i], newpath);
			free(temp);
			i++;
		}
	}
	free(newpath);
	return (shell_execpath_2(paths, commands, shell->evs, token));
}
