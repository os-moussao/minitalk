/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:20:26 by omoussao          #+#    #+#             */
/*   Updated: 2021/12/01 13:22:08 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * This function prints the given string with respect to
 * the flags and dimentions specified in the data variable
 */
static int	out(t_arg_data data, const char *str, int len)
{
	int		window_len;
	char	*out;

	window_len = len;
	if (data.precision >= 0)
		window_len = min(len, data.precision);
	len = max(window_len, data.width);
	if (!len)
		return (len);
	out = malloc(len);
	if (!out)
		return (-1);
	if (data.flags & LEFT_JUSTIFY)
	{
		ft_memcpy(out, str, window_len);
		ft_memset(out + window_len, ' ', len - window_len);
	}
	else
	{
		ft_memset(out, ' ', len - window_len);
		ft_memcpy(out + len - window_len, str, window_len);
	}
	write(1, out, len);
	free(out);
	return (len);
}

/**
 * This function gets the string/character using the variable argument
 * (or it gets the specifier itself if it is not an 's' nor a 'c')
 * it then passes the length, the string, and the argument data to out()
 * to print the result
 */
int	print_string(t_arg_data data, va_list ap)
{
	char	*str;
	char	c;
	int		len;

	if (data.specifier == 's')
	{
		str = va_arg(ap, char *);
		if (!str)
			str = "(null)";
		len = ft_strlen(str);
	}
	else
	{
		if (data.specifier == 'c')
			c = (char)va_arg(ap, int);
		else
			c = data.specifier;
		str = &c;
		len = 1;
	}
	return (out(data, str, len));
}
