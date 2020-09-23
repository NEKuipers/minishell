/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 11:48:27 by nkuipers       #+#    #+#                */
/*   Updated: 2019/11/11 14:12:18 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_atoi_part_two(const char *str, int i, int pn)
{
	unsigned long int	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if ((result > 922337203685477580 || (result == 922337203685477580
			&& (str[i] - '0') > 7)) && pn == 1)
			return (-1);
		else if ((result > 922337203685477580 || (result == 922337203685477580
			&& (str[i] - '0') > 8)) && pn == -1)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * pn);
}

int				ft_atoi(const char *str)
{
	int					i;
	int					pn;
	long int			result;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) ||
			(str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	pn = 1;
	if (str[i] == '-')
	{
		pn = -1;
		i++;
	}
	result = ft_atoi_part_two(str, i, pn);
	return (result);
}
