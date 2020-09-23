/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 14:17:05 by nkuipers       #+#    #+#                */
/*   Updated: 2019/11/12 18:56:23 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*string;
	int		i;
	char	d;

	d = (char)c;
	i = 0;
	string = (char *)s;
	while (string[i] != '\0')
	{
		if (string[i] == d)
			return (&string[i]);
		i++;
	}
	if (d == '\0')
		return (&string[i]);
	else
		return (NULL);
}
