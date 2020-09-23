/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_int_ll.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/19 11:01:32 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/23 10:25:53 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_putnbr_ll_fd_count(long long int nbr, int *rv)
{
	long long int		res;
	long long int		len;

	res = nbr;
	len = 1;
	while (res / 10)
	{
		res /= 10;
		len *= 10;
	}
	while (len)
	{
		if (nbr < 0)
			ft_putchar_fd_count(('0' - nbr / len), 1, rv);
		if (!(nbr < 0))
			ft_putchar_fd_count(('0' + nbr / len), 1, rv);
		nbr %= len;
		len /= 10;
	}
}

int			ft_nbrlen_ll(long long int nbr)
{
	long long int		tmp;
	int					len;

	tmp = nbr;
	len = 0;
	if (nbr == 0)
		len++;
	while (tmp)
	{
		tmp = tmp / 10;
		len++;
	}
	return (len);
}

void		prepare_ll_int(t_flags *flags, long long int *nbr)
{
	if (*nbr < 0)
	{
		flags->signornot = 1;
		flags->sign = '-';
	}
	flags->nbrlen = ft_nbrlen_ll(*nbr);
	if (flags->precision != -2)
		flags->zero = 0;
	if (flags->precision == -2 ||
		(flags->precision < flags->nbrlen && *nbr != 0))
		flags->precision = flags->nbrlen;
}

void		printint_ll(t_flags *flags, va_list list, int *rv)
{
	long long int nbr;

	nbr = va_arg(list, long long int);
	prepare_ll_int(flags, &nbr);
	if (flags->signornot && (flags->zero || flags->leftj))
		ft_putchar_fd_count(flags->sign, 1, rv);
	if (flags->leftj)
	{
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_putnbr_ll_fd_count(nbr, rv);
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
			ft_putnbr_ll_fd_count(nbr, rv);
	}
}
