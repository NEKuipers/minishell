/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 11:04:01 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/01/13 12:10:45 by nkuipers      ########   odam.nl         */
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

int			shell_execpath(t_shell *shell)
{
	char	**paths;
	int		i;
	char	*temp;
	char	*newpath;

	newpath = ft_strjoin("/", shell->args[0]);
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
	return (shell_execpath_2(paths, shell->args, shell->evs));
}

void	pipe_error(t_list *tlist, t_shell *shell)
{
	ft_lstclear(&tlist, &clear_ops);
	free_args(shell->evs);
	free_args(shell->args);
	exit(-1);
}

void	operator_pipe(t_list *tlist, t_shell *shell)
{
	pid_t	pid;
	char	*buff;

	buff = (char *)malloc(sizeof(char) * 1025);
	buff[1025] = '\0';
	if (pipe(shell->fds) == -1)
		pipe_error(tlist, shell);
	pid = fork();
	if (pid < 0)
		pipe_error(tlist, shell);
	if (pid > 0)
	{
		dup2(0, shell->fds[1]);
		close(shell->fds[1]);
	}
	if (pid == 0)
	{
		if (read(shell->fds[0], buff, 1024) < 0)
			pipe_error(tlist, shell);
		dup2(STDIN_FILENO, shell->fds[0]);
		shell->rv = shell_execute(shell, shell->args);
		close(shell->fds[0]);
	}
	free(buff);
}

void	operator_redirect_output(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;
	
	shell->fds[0] = dup(STDOUT_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		ft_printf_fd(2, "%s: no such file or directory\n", filename);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDOUT_FILENO);
	close(fd);
	return ;
}

void	operator_append_output(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;
	
	shell->fds[0] = dup(STDOUT_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
	{
		ft_printf_fd(2, "%s: no such file or directory\n", filename);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDOUT_FILENO);
	close(fd);
	return ;
}

void	operator_redirect_input(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;
	
	shell->fds[0] = dup(STDIN_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_printf_fd(2, "%s: no such file or directory\n", filename);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDIN_FILENO);
	close(fd);
	return ;
}

void	operator_exec(t_list *tlist, t_shell *shell)
{
	if (((t_ops *)(tlist->content))->type == '|')
		operator_pipe(tlist, shell);
	else if (((t_ops *)(tlist->content))->type == '>')
		operator_redirect_output(tlist, shell);
	else if (((t_ops *)(tlist->content))->type == '}')
		operator_append_output(tlist, shell);
	else if (((t_ops *)(tlist->content))->type == '<')
		operator_redirect_input(tlist, shell);
	return ;
}
