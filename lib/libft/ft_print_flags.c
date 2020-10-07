/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_flags.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:28:35 by bmans         #+#    #+#                 */
/*   Updated: 2020/10/07 14:23:48 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		print_width(t_print *print)
{
	if (ft_isdigit(*(print->form)))
	{
		print->width = ft_atoi(print->form);
		while (ft_isdigit(*(print->form)))
			(print->form)++;
	}
	else if (*(print->form) == '*')
	{
		print->width = va_arg(print->ap, int);
		if (print->width < 0)
		{
			print->pad = ' ';
			print->left = 1;
			print->width = -print->width;
		}
		(print->form)++;
	}
}

static void		print_prec(t_print *print)
{
	if (*(print->form) == '.')
	{
		print->prec = 0;
		(print->form)++;
		if (ft_isdigit(*(print->form)))
		{
			print->prec = ft_atoi(print->form);
			while (ft_isdigit(*(print->form)))
				(print->form)++;
		}
		else if (*(print->form) == '*')
		{
			print->prec = va_arg(print->ap, int);
			if (print->prec < 0)
			{
				print->prec = -1;
			}
			(print->form)++;
		}
	}
}

void			ft_print_flags(t_print *print)
{
	while (ft_strchr("-0+ ", *(print->form)) != NULL)
	{
		if (*(print->form) == '-')
			print->left = 1;
		if (*(print->form) == '0' && !print->left)
			print->pad = '0';
		if (*(print->form) == '\0')
			return ;
		(print->form)++;
	}
	print_width(print);
	print_prec(print);
	while (*(print->form) && ft_strchr(CONV_LIST, *(print->form)) == NULL)
		(print->form)++;
	if (*(print->form))
	{
		print->conv = *(print->form);
		if ((print->left || print->prec >= 0) && print->pad == '0' && \
			print->conv != 's' && print->conv != 'c' && print->conv != '%')
			print->pad = ' ';
	}
}
