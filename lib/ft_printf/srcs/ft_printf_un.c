/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_un.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/19 16:16:09 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/23 10:25:55 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			ft_nbrlen_un(unsigned int nbr)
{
	unsigned int	nb;
	int				length;

	nb = nbr;
	length = 0;
	if (nbr == 0)
		length = 1;
	while (nb)
	{
		nb /= 10;
		length++;
	}
	return (length);
}

void		ft_putunsigned_fd(unsigned int n, int fd, int *rv)
{
	if (n > 9)
		ft_putunsigned_fd(n / 10, fd, rv);
	ft_putchar_fd_count((char)(n % 10 + 48), fd, rv);
}

void		prepare_un(t_flags *flags, unsigned int *nbr)
{
	if (flags->length == 'h')
		*nbr = (short)*nbr;
	else if (flags->length == 'H')
		*nbr = (char)*nbr;
	flags->nbrlen = ft_nbrlen_un(*nbr);
	if (flags->precision != -2)
		flags->zero = 0;
	if (flags->precision == -2 ||
		(flags->precision < flags->nbrlen && *nbr != 0))
		flags->precision = flags->nbrlen;
}

void		printun(t_flags *flags, va_list list, int *rv)
{
	unsigned int		nbr;

	nbr = va_arg(list, unsigned int);
	prepare_un(flags, &nbr);
	if (flags->signornot && (flags->leftj || flags->zero))
		ft_putchar_fd_count(flags->sign, 1, rv);
	if (flags->leftj)
	{
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_putunsigned_fd(nbr, 1, rv);
	}
	if (!flags->leftj && flags->zero)
		padder(flags->width, flags->precision, '0', rv);
	else
		padder(flags->width, flags->precision, ' ', rv);
	if (!flags->leftj)
	{
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_putunsigned_fd(nbr, 1, rv);
	}
}
