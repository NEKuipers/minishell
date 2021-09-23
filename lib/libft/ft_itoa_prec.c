/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_prec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:35:55 by bmans         #+#    #+#                 */
/*   Updated: 2021/09/23 15:51:19 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static u_int32_t	ft_digitcount(int n)
{
	unsigned int	digits;

	digits = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

static unsigned int	digitct(int digits, char neg)
{
	if (neg)
		digits += 1;
	return (digits);
}

char	*ft_itoa_prec(int n, int prec)
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
	digits = digitct(digits, neg);
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
