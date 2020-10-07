/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_int.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 13:59:34 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/07 14:23:52 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_int(t_print *print)
{
	int		num;
	char	*nstr;

	num = va_arg(print->ap, int);
	nstr = ft_itoa_prec(num, print->prec);
	if (nstr && print->width > (int)ft_strlen(nstr))
		nstr = ft_print_resize(nstr, print);
	if (!nstr)
	{
		print->form = NULL;
		return ;
	}
	ft_putstr_fd(nstr, print->out);
	print->len += ft_strlen(nstr);
	free(nstr);
}
