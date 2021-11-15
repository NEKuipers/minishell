/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_redirs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 16:13:53 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/15 14:11:50 by bmans         ########   odam.nl         */
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

static char	*heredoc(char *delim)
{
	char	*tmp[3];

	tmp[0] = ft_strdup("");
	while (1)
	{
		tmp[1] = readline("> ");
		if (!tmp[0] || g_signal.sigint)
			break ;
		if (!tmp[1] || !ft_strcmp(delim, tmp[1]))
		{
			free(tmp[1]);
			return (tmp[0]);
		}
		tmp[2] = ft_strjoin(tmp[0], tmp[1]);
		if (!tmp[2])
			break ;
		free(tmp[1]);
		free(tmp[0]);
		tmp[0] = ft_strjoin(tmp[2], "\n");
		free(tmp[2]);
	}
	free(tmp[0]);
	free(tmp[1]);
	return (NULL);
}

void	operator_heredoc(t_shell *shell, t_token *token)
{
	int		fds[2];
	char	*info;

	info = heredoc(token->str);
	if (!info)
		return ;
	ft_close(shell->fdin);
	pipe(fds);
	ft_printf_fd(fds[1], info);
	free(info);
	close(fds[1]);
	dup2(fds[0], STDIN);
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
		signal(SIGINT, &signal_dummy);
		return (2);
	}
	ft_close(fds[0]);
	dup2(fds[1], STDOUT);
	shell->pipout = fds[1];
	shell->pid = pid;
	shell->last = 0;
	return (1);
}
