/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:46:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/02/04 12:18:13 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_list	*skip_redirs(t_list *tlist)
// {
// 	while (((t_ops *)(tlist->content))->type != '\0'
// 		&& ((t_ops *)(tlist->content))->type != '|')
// 		tlist = tlist->next;
// 	return (tlist);
// }


// int		last_command(t_shell *shell, int status)
// {
// 	char	*temp;

// 	if ((shell->rv = shell_execute(shell, shell->args)) == -1)
// 	{
// 		wait(&status);
// 		temp = ft_itoa(WEXITSTATUS(status));
// 		set_new_env(shell->evs, ft_strjoin("PIPESTATUS", temp));
// 		free(temp);
// 	}
// 	ft_printf("test");
// 	wait(&status);
// 	if (dup2(shell->stdin, 0) == -1)
// 		return (1);
// 	return (0);
// }


// int		operator_pipe(t_list *tlist, t_shell *shell)
// {
// 	pid_t		pid;
// 	int			status;
// 	static int	count = 0;

// 	status = 0;
// 	shell->args = ((t_ops *)(tlist->content))->args;
// 	if (count != 0)
// 		if (((t_ops *)(tlist->next->content))->type != '|')
// 			return (last_command(shell, status));
// 	count++;
// 	if (pipe(shell->fds) == -1)
// 		pipe_error(tlist, shell);
// 	pid = fork();
// 	if (pid < 0)
// 		pipe_error(tlist, shell);
// 	if (pid == 0)
// 	{
// 		close(shell->fds[0]);
// 		dup2(shell->fds[1], 1);
// 		shell->rv = shell_execute(shell, shell->args);
// 		close (shell->fds[1]);
// 		exit(0);
// 	}
// 	if (pid > 0)
// 	{
// 		wait (&status);
// 		close(shell->fds[1]);
// 		if (dup2(shell->fds[0], 0) == -1)
// 			return (-1);
// 		close(shell->fds[0]);
// 		if (((t_ops *)(tlist->next->content))->type == '|')
// 			return (operator_pipe(tlist->next, shell));
// 		return (operator_pipe(skip_redirs(tlist), shell));
// 	}
// 	return (0);
// }

