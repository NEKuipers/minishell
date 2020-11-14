/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 12:01:47 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/11/14 10:56:19 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** This function frees strings in an array, and then the top level pointer.
*/

void		free_args(char **args)
{
	int i;

	i = 0;
	if (args)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

/*
** These functions are called instead of the usual ctrl-c and ctrl-\
** behaviour. The backslashes are used to remove the '^C' and '^\' that would
** otherwise appear in the command line and overwrite them with spaces.
*/

void		ctrlchandler(int n)
{
	(void)n;
	ft_printf("\b\b  \n<$ ");
}

void		ctrlbshandler(int n)
{
	(void)n;
	ft_printf("\b\b  \b\b");
	return ;
}

/*
** This function finds the correct ev in the array and returns its position.
*/

int			find_ev(char **evs, char *target)
{
	int		i;

	i = 0;
	while (ft_strncmp(evs[i], target, ft_strlen(target)) != 0)
		i++;
	return (i);
}
