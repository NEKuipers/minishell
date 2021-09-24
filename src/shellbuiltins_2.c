/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 10:05:56 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/09/24 09:21:43 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** This is echo. It prints all arguments back with one space in between and a
** nline at the end, except for when the -n flag is given.
*/

int	shell_echo(t_shell *shell)
{
	int	i;
	int	nflag;

	i = 1;
	nflag = 0;
	while (shell->args[i])
	{
		if (ft_strncmp(shell->args[i], "-n", 3) == 0)
		{
			i++;
			nflag = 1;
		}
		if (shell->args[i] == NULL)
			return (0);
		else if (shell->args[i + 1] == NULL && nflag == 0)
			ft_printf("%s\n", shell->args[i]);
		else if (shell->args[i + 1] == NULL)
			ft_printf("%s", shell->args[i]);
		else
			ft_printf("%s ", shell->args[i]);
		i++;
	}
	return (0);
}

/*
** This is a recreation of cat. It opens the target argument and
** reads and prints the contents, line by line.
*/

/*int		shell_cat(t_shell *shell)
{
	int		fd;
	char	*line;

	fd = open(shell->args[1], O_RDONLY);

	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (line)
			free(line);
	}
	close(fd);
	return (0);
}*/

/*
** Free the malloced stuff and exit.
*/

void	clear_ops(void *ops)
{
	free(((t_ops *)ops)->operation);
	free_args(((t_ops *)ops)->args);
	free(ops);
}

int	shell_exit(t_shell *shell)
{
	free_args(shell->evs);
	ft_lstclear(&(shell->ops), &clear_ops);
	exit(0);
	return (0);
}
