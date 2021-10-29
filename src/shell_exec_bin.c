/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec_bin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 11:36:39 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/29 11:33:09 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	pid_error(char **paths, char **args)
{
	free_array(args);
	free_array(paths);
	exit(1);
}

static void	shell_execpath_3(char **paths, char **args, char **evs, int i)
{
	char	*temp;

	temp = ft_strdup(paths[i]);
	free_array(paths);
	execve(temp, args, evs);
}

static int	shell_execpath_2(char **paths, char **args, \
	char **evs, t_token *token)
{
	int			i;
	struct stat	buf;
	int			rv;

	i = 0;
	if (ft_strncmp(args[0], "./", 2) == 0)
		paths = set_new_env(paths, args[0], 1);
	g_signal.pid = fork();
	if (g_signal.pid == 0)
	{
		while (paths[i])
		{
			if (stat(paths[i], &buf) == 0)
				shell_execpath_3(paths, args, evs, i);
			i++;
		}
		ft_printf("minishell: command not found: %s.\n", args[0]);
		free_tokens(token);
		pid_error(paths, args);
	}
	waitpid(g_signal.pid, &rv, 0);
	if (g_signal.sigint == 1 || g_signal.sigquit == 1)
		return (g_signal.exit_status);
	free_array(paths);
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
