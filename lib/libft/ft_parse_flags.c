/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parse_flags.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 10:35:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/01 17:10:22 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	parse_length(char **start, t_flags *flags)
{
	while (*start)
	{
		if (**start == 'h' && flags->length == 'h')
			flags->length = 'H';
		else if (**start == 'h')
			flags->length = 'h';
		else if (**start == 'l' && flags->length == 'l')
			flags->length = 'L';
		else if (**start == 'l')
			flags->length = 'l';
		else
			break ;
		(*start)++;
	}
}

void	parse_precision(char **start, t_flags *flags, va_list list)
{
	flags->precision = -2;
	if (**start != '.')
		return ;
	else
	{
		(*start)++;
		while (**start)
		{
			if (ft_isdigit(**start) || **start == '-')
			{
				flags->precision = ft_atoi(*start);
				return ;
			}
			else
			{
				flags->precision = (**start == '*') ? va_arg(list, int) : 0;
				break ;
			}
			(*start)++;
		}
		while (ft_isdigit(**start))
			(*start)++;
	}
}

void	parse_width(char **start, t_flags *flags, va_list list)
{
	while (**start)
	{
		if (**start == '.')
			break ;
		if (**start == '*')
		{
			flags->width = va_arg(list, int);
			(*start)++;
			return ;
		}
		else if (**start >= 0 || **start <= 9)
		{
			flags->width = ft_atoi(*start);
			break ;
		}
		else
			break ;
		(*start)++;
	}
	while (ft_isdigit(**start))
		(*start)++;
}

void	parse_flags(char **start, t_flags *flags)
{
	while (*start)
	{
		if (**start == '+')
			flags->sign = '+';
		else if (**start == '0')
			flags->zero = 1;
		else if (**start == ' ')
			flags->sign = ' ';
		else if (**start == '-')
			flags->leftj = 1;
		else if (**start == '#')
			flags->hash = 1;
		else
			break ;
		(*start)++;
	}
}
