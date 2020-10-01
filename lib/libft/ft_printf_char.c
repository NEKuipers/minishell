/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_char.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:37:29 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/01 17:10:45 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd_count(char c, int fd, int *rv)
{
	write(fd, &c, 1);
	*rv += 1;
}

void	printchar(t_flags *flags, va_list list, int *rv)
{
	if (flags->width == 0 || flags->width == 1)
		ft_putchar_fd_count(va_arg(list, int), 1, rv);
	else if (flags->width > 1 && flags->leftj == 0)
	{
		while (flags->width > 1)
		{
			ft_putchar_fd_count((flags->zero == 1 ? '0' : ' '), 1, rv);
			flags->width--;
		}
		ft_putchar_fd_count(va_arg(list, int), 1, rv);
		return ;
	}
	else if (flags->width > 1 && flags->leftj == 1)
	{
		ft_putchar_fd_count(va_arg(list, int), 1, rv);
		while (flags->width > 1)
		{
			ft_putchar_fd_count((flags->zero == 1 ? '0' : ' '), 1, rv);
			flags->width--;
		}
		return ;
	}
}

void	print_percent(t_flags *flags, int *rv)
{
	if (flags->width == 0 || flags->width == 1)
		ft_putchar_fd_count('%', 1, rv);
	else if (flags->width > 1 && flags->leftj == 0)
	{
		while (flags->width > 1)
		{
			ft_putchar_fd_count((flags->zero == 1 ? '0' : ' '), 1, rv);
			flags->width--;
		}
		ft_putchar_fd_count('%', 1, rv);
		return ;
	}
	else if (flags->width > 1 && flags->leftj == 1)
	{
		ft_putchar_fd_count('%', 1, rv);
		while (flags->width > 1)
		{
			ft_putchar_fd_count((flags->zero == 1 ? '0' : ' '), 1, rv);
			flags->width--;
		}
		return ;
	}
}
