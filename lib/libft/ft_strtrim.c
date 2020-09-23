/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:51:25 by nkuipers       #+#    #+#                */
/*   Updated: 2019/11/13 16:38:54 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	char_check(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*beg;
	char	*end;
	char	*new;

	if (s1 == 0)
		return (NULL);
	beg = (char *)s1;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (char_check(set, *beg))
		beg++;
	while (char_check(set, *end) && &*end != &s1[0])
		end--;
	end++;
	new = (char*)malloc((beg >= end) ? 1 : (end - beg + 1));
	if (new == 0)
		return (NULL);
	if (beg >= end)
		new[0] = '\0';
	else
		ft_strlcpy(new, beg, (end - beg + 1));
	return (new);
}
