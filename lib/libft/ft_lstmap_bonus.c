/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 17:18:47 by nkuipers       #+#    #+#                */
/*   Updated: 2019/11/12 18:58:23 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *newstart;
	t_list *new;

	if (!lst)
		return (0);
	new = ft_lstnew(f(lst->content));
	if (!(new))
		return (0);
	lst = lst->next;
	newstart = new;
	while (lst)
	{
		new->next = (ft_lstnew(f(lst->content)));
		if (!new)
		{
			ft_lstclear(&newstart, del);
			return (0);
		}
		new = new->next;
		lst = lst->next;
	}
	return (newstart);
}
