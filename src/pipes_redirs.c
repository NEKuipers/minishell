/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_redirs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 16:13:53 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/03 15:22:12 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	operator_redirect(t_shell *shell, t_token *token, int type)
{
	ft_close(shell->fdout);
	if (type == TRUNC)
		shell->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		shell->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (shell->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->rv = 1;
		shell->no_exec = 1;
		return ;
	}
	dup2(shell->fdout, STDOUT);
}

void	operator_heredoc(t_shell *shell, t_token *token)
{
	ft_close(shell->fdin);
	return ;
}

void	operator_input(t_shell *shell, t_token *token)
{
	ft_close(shell->fdin);
	shell->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (shell->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->rv = 1;
		shell->no_exec = 1;
		return ;
	}
	dup2(shell->fdin, STDIN);
}

int	operator_pipe(t_shell *shell)
{
	pid_t	pid;
	int		fds[2];

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		ft_close(fds[1]);
		dup2(fds[0], STDIN);
		shell->pipin = fds[0];
		shell->pid = -1;
		shell->parent = 0;
		shell->no_exec = 0;
		return (2);
	}
	ft_close(fds[0]);
	dup2(fds[1], STDOUT);
	shell->pipout = fds[1];
	shell->pid = pid;
	shell->last = 0;
	return (1);
}
