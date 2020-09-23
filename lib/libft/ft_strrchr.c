/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 14:11:36 by nkuipers       #+#    #+#                */
/*   Updated: 2019/11/12 18:56:07 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	char	d;

	d = (char)c;
	temp = 0;
	while (*s && *s != '\0')
	{
		if (*s == d)
			temp = (char*)s;
		s++;
	}
	if (d == '\0')
		return ((char*)s);
	if (temp != 0)
		return (temp);
	else
		return (0);
}
