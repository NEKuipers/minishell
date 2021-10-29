/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec_bin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 11:36:39 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/29 11:02:36 by nkuipers      ########   odam.nl         */
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
	int			pid;
	int			i;
	struct stat	buf;

	i = 0;
	if (ft_strncmp(args[0], "./", 2) == 0)
		paths = set_new_env(paths, args[0], 1);
	pid = fork();
	if (pid == 0)
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
	else if (pid < 0)
		pid_error(paths, args);
	free_array(paths);
	wait(0);
	return (0);
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
