/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nbrlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 11:09:36 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/09/24 09:29:34 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int nb)
{
	int	length;

	length = 0;
	if (nb < 0)
		length++;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		length++;
	}
	return (length);
}
