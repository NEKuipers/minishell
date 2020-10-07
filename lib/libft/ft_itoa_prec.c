/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_prec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:35:55 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/07 14:24:26 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static u_int32_t	ft_digitcount(int n)
{
	unsigned int digits;

	digits = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char				*ft_itoa_prec(int n, int prec)
{
	char			*a;
	unsigned int	digits;
	char			neg;

	if (prec == 0 && n == 0)
		return (ft_strdup(""));
	neg = (n < 0);
	digits = ft_digitcount(n);
	if (digits < (u_int32_t)prec && prec != -1)
		digits = prec;
	digits += (neg ? 1 : 0);
	a = malloc(sizeof(char) * (digits + 1));
	if (a)
	{
		a[digits] = 0;
		while (digits > 0)
		{
			digits--;
			a[digits] = ((n > 0) ? (n % 10) : -(n % 10)) + '0';
			n = (n > 0) ? (n / 10) : -(n / 10);
		}
		if (neg)
			a[0] = '-';
	}
	return (a);
}
