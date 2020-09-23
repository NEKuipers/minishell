/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 09:44:03 by nkuipers       #+#    #+#                */
/*   Updated: 2019/11/13 15:26:57 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_nbrlen(int nb)
{
	int length;

	length = (nb < 0) ? 1 : 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		length++;
	}
	return (length);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == 0)
		return (0);
	if (n == -2147483648)
		ft_strlcpy(str, "-2147483648", 12);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		ft_strlcpy(str, "0", 2);
	while (n > 0)
	{
		str[len - 1] = (n % 10 + 48);
		n /= 10;
		len--;
	}
	return (str);
}
