/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 14:50:19 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 11:49:35 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t diff;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	diff = dstsize - i;
	if (diff == 0)
		return (i + ft_strlen(src));
	j = 0;
	while (diff > 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
		diff--;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
