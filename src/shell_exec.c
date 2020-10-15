/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 11:04:01 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/15 15:26:36 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** This is where it starts getting interesting. Most shell commands are programs
** in a /bin/ folder. To run it, we need to fork() our process to create a new
** process. We then have two processes which run concurrently, distinguished by
** their rv. A child process returns 0 while the parent process returns its
** processID (or pid). We make the process with pid = 0 (the child) execute (or
** execve()) ls. The parent process waits by calling wait() until the child is
** done and terminated, and then returns.
** If fork() returns a negative value, there has been an error and we exit.
**
** To access programs in the various /bin/ folders in the path, we add
** /[argument] to every bin folder and attempt to run them. Stat() is used
** to check if the executable exists before running.
** There's a lot of freeing going on since we need to make sure we free in
** both the parent and child processes.
*/

static void	shell_execpath_3(char **paths, char **args, char **evs, int i)
{
	char *temp;

	temp = ft_strdup(paths[i]);
	free_args(paths);
	execve(temp, args, evs);
}

static int	pid_error(char **paths, char **args, char **evs)
{
	free_args(args);
	free_args(evs);
	free_args(paths);
	exit(-1);
}

static int	shell_execpath_2(char **paths, char **args, char **evs)
{
	int			pid;
	int			i;
	struct stat	buf;

	i = 0;
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
		pid_error(paths, args, evs);
	}
	else if (pid < 0)
		pid_error(paths, args, evs);
	free_args(paths);
	wait(0);
	return (0);
}

#include <stdio.h>

int			shell_execpath(char **args, char **evs)
{
	char	**paths;
	int		i;
	char	*temp;
	char	*newpath;

	newpath = ft_strjoin("/", args[0]);
	i = find_ev(evs, "PATH=");
	paths = ft_split(&evs[i][5], ':');
	i = 0;
	paths = set_new_env(paths, "/");
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], newpath);
		free(temp);
		printf("%s\n", paths[i]);
		i++;
	}
	free(newpath);
	return (shell_execpath_2(paths, args, evs));
}
