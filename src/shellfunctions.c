/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellfunctions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 11:04:01 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 11:16:34 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		shell_ls(char **args, char **evs)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		execve("/bin/ls", args, evs);
	}
	else if (pid < 0)
	{
		free_args(args);
		free_args(evs);
		exit(-1);
	}
	wait(0);
	return (0);
}
