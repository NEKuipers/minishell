/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_hex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 10:19:20 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/23 10:25:49 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	prepare_hex(t_flags *flags, unsigned int *nbr)
{
	if (flags->length == 'h')
		*nbr = ((unsigned short)*nbr);
	if (flags->length == 'H')
		*nbr = ((unsigned char)*nbr);
	flags->nbrlen = ft_nbrlen_hex(*nbr);
	if (flags->precision != -2)
		flags->zero = 0;
	if (*nbr == 0)
		flags->hash = 0;
	if (flags->precision == -2 ||
		(flags->precision < flags->nbrlen && *nbr != 0))
		flags->precision = flags->nbrlen;
}

void	printhex_lower(t_flags *flags, va_list list, int *rv)
{
	unsigned int nbr;

	nbr = va_arg(list, unsigned int);
	prepare_hex(flags, &nbr);
	if (flags->hash && nbr != 0 && (flags->leftj || flags->zero))
		ft_putnstr_fd_count("0x", 1, 2, rv);
	if (flags->leftj)
	{
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_puthex_lower_count(nbr, rv);
	}
	if (!flags->leftj && flags->zero)
		padder(flags->width, flags->precision + (flags->hash * 2), '0', rv);
	else
		padder(flags->width, flags->precision + (flags->hash * 2), ' ', rv);
	if (!flags->leftj)
	{
		if (flags->hash && nbr != 0 && !flags->zero)
			ft_putnstr_fd_count("0x", 1, 2, rv);
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_puthex_lower_count(nbr, rv);
	}
}

void	printhex_upper(t_flags *flags, va_list list, int *rv)
{
	unsigned int nbr;

	nbr = va_arg(list, unsigned int);
	prepare_hex(flags, &nbr);
	if (flags->hash && nbr != 0 && (flags->leftj || flags->zero))
		ft_putnstr_fd_count("0X", 1, 2, rv);
	if (flags->leftj)
	{
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_puthex_upper_count(nbr, rv);
	}
	if (!flags->leftj && flags->zero)
		padder(flags->width, flags->precision + (flags->hash * 2), '0', rv);
	else
		padder(flags->width, flags->precision + (flags->hash * 2), ' ', rv);
	if (!flags->leftj)
	{
		if (flags->hash && nbr != 0 && !flags->zero)
			ft_putnstr_fd_count("0X", 1, 2, rv);
		padder(flags->precision, flags->nbrlen, '0', rv);
		if (flags->precision)
			ft_puthex_upper_count(nbr, rv);
	}
}

void	printhex(char **start, t_flags *flags, va_list list, int *rv)
{
	if (**start == 'X')
		printhex_upper(flags, list, rv);
	else if (**start == 'x')
		printhex_lower(flags, list, rv);
}
