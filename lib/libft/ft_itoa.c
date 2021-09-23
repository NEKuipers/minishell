/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 09:44:03 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/09/23 15:47:27 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_itoa(int n)
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
