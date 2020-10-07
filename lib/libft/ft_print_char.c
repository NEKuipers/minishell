/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_char.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 13:59:42 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/07 14:23:55 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char(t_print *print)
{
	int c;

	if (print->conv == '%')
		c = '%';
	else
		c = va_arg(print->ap, int);
	if (print->width > 1 && !print->left)
		ft_putnchar_fd(print->pad, print->width - 1, print->out);
	ft_putchar_fd(c, print->out);
	if (print->width > 1 && print->left)
		ft_putnchar_fd(print->pad, print->width - 1, print->out);
	(print->len) += print->width > 1 ? print->width : 1;
}
