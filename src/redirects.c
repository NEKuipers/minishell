/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 12:26:13 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/02/05 09:45:32 by nkuipers      ########   odam.nl         */
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

int		operator_exec(t_list *tlist, t_shell *shell)
{
	if (((t_ops *)(tlist->content))->type == '|')
		return(operator_pipe(tlist, shell));
	else if (((t_ops *)(tlist->content))->type == '>')
		return(operator_redirect_output(tlist, shell));
	else if (((t_ops *)(tlist->content))->type == '}')
		return(operator_append_output(tlist, shell));
	else if (((t_ops *)(tlist->content))->type == '<')
		return(operator_redirect_input(tlist, shell));
	else
		return (-1);
}
