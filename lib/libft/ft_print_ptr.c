/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_ptr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 13:58:55 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/07 14:24:00 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_ptr(t_print *print)
{
	u_int64_t	ptr;
	char		*tpstr;
	char		*pstr;

	ptr = va_arg(print->ap, u_int64_t);
	pstr = NULL;
	tpstr = ft_itoa_base_prec(ptr, "0123456789abcdef", print->prec);
	if (tpstr)
	{
		pstr = ft_strjoin("0x", tpstr);
		free(tpstr);
	}
	if (pstr && print->width > (int)ft_strlen(pstr))
		pstr = ft_print_resize(pstr, print);
	if (!pstr)
	{
		print->form = NULL;
		return ;
	}
	ft_putstr_fd(pstr, print->out);
	print->len += ft_strlen(pstr);
	free(pstr);
}
