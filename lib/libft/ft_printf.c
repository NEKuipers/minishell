/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 09:44:57 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/01 17:11:10 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_store_rv(va_list list, int *rv)
{
	int	*temp;

	temp = va_arg(list, int *);
	*temp = *rv;
}

int		parse_spec(char **start, t_flags *flags, va_list list, int *rv)
{
	while (**start != 's' && **start != 'c' && **start != 'i' && **start != 'd'
		&& **start != 'x' && **start != 'X' && **start != 'u' && **start != 'p'
		&& **start != 'n')
		(*start)++;
	if (**start == 's')
		printstr(flags, list, rv);
	else if (**start == 'c')
		printchar(flags, list, rv);
	else if (**start == 'i' || **start == 'd')
		printint(flags, list, rv);
	else if (**start == 'u')
		printun(flags, list, rv);
	else if (**start == 'x' || **start == 'X')
		printhex(start, flags, list, rv);
	else if (**start == 'p')
		printptr(flags, list, rv);
	else if (**start == 'n')
		ft_store_rv(list, rv);
	else
		return (0);
	return (1);
}

void	parse_hub(char **start, t_flags *flags, va_list list, int *rv)
{
	parse_flags(start, flags);
	if (flags->sign != 0)
		flags->signornot = 1;
	parse_width(start, flags, list);
	if (flags->width < 0)
	{
		flags->leftj = 1;
		flags->width *= -1;
	}
	parse_precision(start, flags, list);
	parse_length(start, flags);
	if (**start == '%')
		print_percent(flags, rv);
	else
		parse_spec(start, flags, list, rv);
}

int		ft_printf(const char *input, ...)
{
	t_flags	flags;
	va_list list;
	int		rv;

	rv = 0;
	va_start(list, input);
	while (*input != '\0')
	{
		if (*input != '%')
			ft_putchar_fd_count(*input, 1, &rv);
		else
		{
			input++;
			ft_bzero(&flags, (sizeof(t_flags)));
			parse_hub((char **)&input, &flags, list, &rv);
		}
		input++;
	}
	va_end(list);
	return (rv);
}
