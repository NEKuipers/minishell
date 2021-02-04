/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 12:26:13 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/02/04 18:08:20 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int 	operator_redirect_output(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;

	shell->fds[0] = dup(STDOUT_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDOUT_FILENO);
	close(fd);
	return (0);
}

int 	operator_append_output(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;

	shell->fds[0] = dup(STDOUT_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDOUT_FILENO);
	close(fd);
	return (0);
}

int 	operator_redirect_input(t_list *tlist, t_shell *shell)
{
	int		fd;
	char	*filename;

	shell->fds[0] = dup(STDIN_FILENO);
	filename = ((t_ops *)(tlist->next->content))->args[0];
	if ((fd = open(filename, O_RDONLY)) == -1)
    {
		ft_printf_fd(2, "%s: no such file or directory\n", filename);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	shell->rv = shell_execute(shell, shell->args);
	dup2(shell->fds[0], STDIN_FILENO);
	close(fd);
	return (0);
}

int		operator_pipe(t_list *tlist, t_shell *shell)
{
<<<<<<< HEAD:src/redirects.c
	pid_t		pid;
=======
	pid_t	pid;
	t_ops	*op;

	op = (t_ops *)(tlist->content);
	if (pipe(op->pipefds))
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	else if (pid == 0)
	{
		shell->fds[1] = dup(1);
		close(op->pipefds[0]);
		dup2(op->pipefds[1], 1);
		shell->rv = shell_execute(shell, shell->args);
		close(op->pipefds[1]);
		exit(0);
	}
	shell->fds[0] = dup(0);
	close(op->pipefds[1]);
	dup2(op->pipefds[0], 0);
	waitpid(pid, 0, 0);

/*	pid_t	pid;
	char	*buff;
>>>>>>> f8e6df4da522184bb866f80be2af48eb5cca918c:src/pipes_and_redirects.c

	shell->args = ((t_ops *)(tlist->content))->args;
	if (pipe(shell->fds) == -1)
		pipe_error(tlist, shell);
	pid = fork();
	if (pid == 0)
	{
		close (shell->fds[0]);
		dup2(shell->fds[1], 1);
		shell->rv = shell_execute(shell, shell->args);
		close (shell->fds[1]);
		exit(0);
	}
<<<<<<< HEAD:src/redirects.c
	wait(0);
	close(shell->fds[1]);
	shell->stdin = dup(0);
	if (dup2(shell->fds[0], 0) == -1)
		return (-1);
	close(shell->fds[0]);
	return (0);
=======
	free(buff); */
>>>>>>> f8e6df4da522184bb866f80be2af48eb5cca918c:src/pipes_and_redirects.c
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
