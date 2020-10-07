/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_string.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 13:58:47 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/07 14:24:06 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_string(t_print *print)
{
	char	*tstr;
	char	*str;

	tstr = va_arg(print->ap, char*);
	if (!tstr)
		tstr = "(null)";
	if ((int)ft_strlen(tstr) < print->prec || print->prec == -1)
		print->prec = (int)ft_strlen(tstr);
	str = malloc(sizeof(char) * (print->prec + 1));
	if (str)
	{
		ft_strlcpy(str, tstr, print->prec + 1);
		if (print->width > (int)ft_strlen(str))
			str = ft_print_resize(str, print);
	}
	if (!str)
	{
		print->form = NULL;
		return ;
	}
	ft_putstr_fd(str, print->out);
	print->len += ft_strlen(str);
	free(str);
}
