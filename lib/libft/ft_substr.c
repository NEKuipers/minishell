/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 17:48:46 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 15:22:40 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*empty_string(char *new)
{
	new = malloc(1);
	new[0] = '\0';
	return (new);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = 0;
	i = 0;
	if (s == 0)
		return (NULL);
	if (start > ft_strlen(s))
		return (empty_string(new));
	if (start + len <= ft_strlen(s))
		new = (char *)malloc(sizeof(char) * (len + 1));
	else
		new = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	if (new == 0)
		return (NULL);
	j = start;
	while (j < start + len && s[j])
	{
		new[i] = s[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
