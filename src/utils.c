/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 12:01:47 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/23 12:02:22 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_exit(char **evs)
{
	int i;

	i = 0;
	while (evs[i])
	{
		free(evs[i]);
		i++;
	}
	free(evs);
	exit(0);
}
