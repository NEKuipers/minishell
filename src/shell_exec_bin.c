/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec_bin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 11:36:39 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/14 16:58:08 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell_exec_error(char *path)
{
	DIR	*folder;
	int	fd;
	int	returnvalue;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_printf_fd(STDERR, "minishell: %s", path);
	if (ft_strchr(path, '/') == NULL)
		ft_printf_fd(STDERR, ": command not found\n");
	else if (fd == -1 && folder == NULL)
		ft_printf_fd(STDERR, ": no such file or directory\n");
	else if (fd == -1 && folder != NULL)
		ft_printf_fd(STDERR, ": is a directory\n");
	else if (fd != -1 && folder == NULL)
		ft_printf_fd(STDERR, ": permission denied\n");
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		returnvalue = 127;
	else
		returnvalue = 126;
	if (folder)
		closedir(folder);
	close(fd);
	return (returnvalue);
}

static int	pid_error(char **paths, char **args, char **evs)
{
	free_array(args);
	free_array(evs);
	free_array(paths);
	exit(-1);
}

int	find_ev(char **evs, char *target)
{
	int		i;

	i = 0;
	while (ft_strncmp(evs[i], target, ft_strlen(target)) != 0)
		i++;
	return (i);
}

static void	shell_execpath_3(char **paths, char **args, char **evs, int i)
{
	char	*temp;

	temp = ft_strdup(paths[i]);
	free_array(paths);
	execve(temp, args, evs);
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
	free_array(paths);
	wait(0);
	return (0);
}

char	**set_new_env(char **evs, char *arg)
{
	int		i;
	char	**ret;

	i = 0;
	while (evs[i])
		i++;
	ret = malloc((i + 2) * (sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (evs[i])
	{
		ret[i] = ft_strdup(evs[i]);
		i++;
	}
	if (ft_strchr(arg, '=') != NULL)
		ret[i] = ft_strdup(arg);
	else
		ret[i] = ft_strjoin(arg, "=''");
	i++;
	ret[i] = NULL;
	free_array(evs);
	return (ret);
}

int	execute_bin(char **commands, t_shell *shell)
{
	char	**paths;
	int		i;
	char	*temp;
	char	*newpath;
	int		returnvalue;

	returnvalue = 127;
	newpath = ft_strjoin("/", commands[0]);
	i = find_ev(shell->evs, "PATH=");
	paths = ft_split(&((shell->evs)[i][5]), ':');
	i = 0;
	paths = set_new_env(paths, "/");
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], newpath);
		free(temp);
		i++;
	}
	free(newpath);
	return (shell_execpath_2(paths, commands, shell->evs));
}
