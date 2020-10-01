/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_int.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:14:21 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/01 17:10:58 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_nbrlen(int nbr)
{
	int length;
	int nb;

	nb = nbr;
	length = (nb < 0) ? 1 : 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		length++;
	}
	return (length);
}

void		ft_putnbr_fd_count(int n, int fd, int *rv)
{
	if (n == -2147483648)
	{
		write(fd, "2", 1);
		n = 147483648;
		*rv += 1;
	}
	if (n > 9)
		ft_putnbr_fd_count(n / 10, fd, rv);
	ft_putchar_fd_count((char)(n % 10 + 48), fd, rv);
}

void		prepare_int(t_flags *flags, int *nbr)
{
	if (flags->length == 'h')
		*nbr = (short)*nbr;
	else if (flags->length == 'H')
		*nbr = (char)*nbr;
	if (*nbr < 0)
	{
		flags->sign = '-';
		*nbr *= -1;
	}
	if (flags->sign != 0)
		flags->signornot = 1;
	if (flags->precision != -2)
		flags->zero = 0;
	flags->nbrlen = ft_nbrlen(*nbr);
	if (flags->precision == -2 ||
		(flags->precision < flags->nbrlen && *nbr != 0))
		flags->precision = flags->nbrlen;
}

void		printint_reg(t_flags *flags, va_list list, int *rv)
{
	int		nbr;

	nbr = va_arg(list, int);
	prepare_int(flags, &nbr);
	if (flags->signornot && (flags->leftj || flags->zero))
		ft_putchar_fd_count(flags->sign, 1, rv);
	if (flags->leftj)
	{
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_putnbr_fd_count(nbr, 1, rv);
	}
	if (!flags->leftj && flags->zero)
		padder(flags->width, flags->precision + flags->signornot, '0', rv);
	else
		padder(flags->width, flags->precision + flags->signornot, ' ', rv);
	if (!flags->leftj)
	{
		if (flags->signornot && !flags->zero)
			ft_putchar_fd_count(flags->sign, 1, rv);
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_putnbr_fd_count(nbr, 1, rv);
	}
}

void		printint(t_flags *flags, va_list list, int *rv)
{
	if (flags->length == 'l')
		printint_l(flags, list, rv);
	else if (flags->length == 'L')
		printint_ll(flags, list, rv);
	else
		printint_reg(flags, list, rv);
}
