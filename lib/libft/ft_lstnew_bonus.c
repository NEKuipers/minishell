/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 17:12:36 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 15:21:07 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list *newlst;

	newlst = (t_list *)malloc(sizeof(t_list));
	if (newlst == 0)
		return (NULL);
	newlst->content = content;
	newlst->next = NULL;
	return (newlst);
}
