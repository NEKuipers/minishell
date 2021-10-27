/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_prec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:35:55 by bmans         #+#    #+#                 */
/*   Updated: 2021/10/27 14:13:12 by nkuipers      ########   odam.nl         */
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

static int	ternaryfixone(int n)
{
	int	o;

	if (n > 0)
		o = n % 10;
	else
		o = -(n % 10);
	return (o + '0');
}

static int	ternaryfixtwo(int n)
{
	if (n > 0)
		n = n / 10;
	else
		n = -(n / 10);
	return (n);
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
			a[digits] = ternaryfixone(n);
			n = ternaryfixtwo(n);
		}
		if (neg)
			a[0] = '-';
	}
	return (a);
}
