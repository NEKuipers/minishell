/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:46:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/05/06 16:13:12 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	operator_pipe(t_list *tlist, t_shell *shell, t_pipeline *pipeline)
{
	int		i;
	pid_t	pid;

	i = pipeline->pipecount;
	// ft_printf("pipecount is %d\nwrite end is %d\nread end is %d\n", i, pipeline->pipes[i], pipeline->pipes[i+1]);
	// shell->args = ((t_ops *)(tlist->content))->args; 
	pid = fork();
	if (pid < 0)
		pipe_error(tlist, shell);
	if (pid == 0)
	{
		close(pipeline->pipes[i]);
		// dupclose_fd(shell->prev_pipe, STDIN_FILENO);
		dup2(pipeline->pipes[i + 1], 1);
		shell->rv = shell_execute(shell, shell->args);
		close (pipeline->pipes[i + 1]);
		exit(0);
	}
	wait(0);
	close(pipeline->pipes[i + 1]);
	// shell->prev_pipe = pipeline->pipes[i];
	if (dup2(pipeline->pipes[i], 0) == -1)
		return (-1);
	close(pipeline->pipes[i]);
	return (0);
}
