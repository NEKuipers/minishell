/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_string.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 12:04:33 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/23 10:25:55 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	padder(int width, int precision, char pad, int *rv)
{
	while (width > precision)
	{
		ft_putchar_fd_count(pad, 1, rv);
		width--;
	}
}

void	ft_putnstr_fd_count(char *s, int fd, int n, int *rv)
{
	int i;

	i = 0;
	if (s == 0)
		return ;
	while (s[i] && i < n)
	{
		ft_putchar_fd_count(s[i], fd, rv);
		i++;
	}
}

void	printstr(t_flags *flags, va_list list, int *rv)
{
	int		len;
	char	*temp;

	temp = va_arg(list, char *);
	if (!temp)
		temp = "(null)";
	len = ft_strlen(temp);
	if (flags->precision < 0 || flags->precision > len)
		flags->precision = len;
	if (flags->leftj == 1)
		ft_putnstr_fd_count(temp, 1, flags->precision, rv);
	if (flags->leftj == 0 && flags->zero == 1)
		padder(flags->width, flags->precision, '0', rv);
	else
		padder(flags->width, flags->precision, ' ', rv);
	if (flags->leftj == 0)
		ft_putnstr_fd_count(temp, 1, flags->precision, rv);
}
