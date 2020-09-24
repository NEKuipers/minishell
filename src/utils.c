/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 12:01:47 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 15:30:26 by nkuipers      ########   odam.nl         */
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
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	if (args)
		free(args);
}

/*
** These functions are called instead of the usual ctrl-c and ctrl-\
** behaviour. The backslashes are used to remove the '^C' and '^\' that would
** otherwise appear in the command line and overwrite them with spaces.
*/

void		ctrlchandler(int n)
{
	(void)n;
	ft_printf("\b\b  \n=> ");
}

void		ctrlbshandler(int n)
{
	(void)n;
	ft_printf("\b\b  \b\b");
	return ;
}
