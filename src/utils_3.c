/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 11:44:48 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/19 11:45:09 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_to_dummy(void)
{
	signal(SIGQUIT, &signal_dummy);
	signal(SIGINT, &signal_dummy);
}
