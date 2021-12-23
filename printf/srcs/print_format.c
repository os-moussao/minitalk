/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:07:10 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/30 22:46:39 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_argument(t_arg_data data, va_list ap)
{
	int		ret;
	int		tmp;
	char	sp;

	ret = 0;
	sp = data.specifier;
	if (sp == 'd' || sp == 'i' || sp == 'u'
		|| sp == 'x' || sp == 'X' || sp == 'p')
	{
		tmp = print_number(data, ap);
		if (tmp == -1)
			return (-1);
		ret += tmp;
	}
	else
	{
		tmp = print_string(data, ap);
		if (tmp == -1)
			return (-1);
		ret += tmp;
	}
	return (ret);
}

/**
 * This function prints and iterates through the characters
 * in the format string, when '%' is encountered, it calls
 * get_arg_data() to get the argument data, and calls print_argument()
 * to print the argument.
 */
int	print_format(const char *format, va_list ap, bool parse)
{
	int			ret;
	int			tmp;
	t_arg_data	data;

	ret = 0;
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format++, 1);
			ret++;
		}
		else
		{
			get_arg_data(&data, &format, parse);
			tmp = print_argument(data, ap);
			if (tmp == -1)
				return (-1);
			ret += tmp;
			if (!*format)
				break ;
			format++;
		}
	}
	return (ret);
}
