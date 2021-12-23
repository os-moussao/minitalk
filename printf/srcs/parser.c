/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:28:35 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/30 22:32:54 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static bool	is_flag(char c)
{
	return (c == '0' || c == '-' || c == '#'
		|| c == ' ' || c == '+');
}

/**
 * Function that initializes argument data
 */
static void	data_init(t_arg_data *data)
{
	data->flags = 0U;
	data->width = 0;
	data->precision = -1;
}

/**
 * When (parse == true) this function gets a number (either the
 * width or the precision) from the format string, and increments the
 * format pointer along the way.
 */
static int	fmt_atoi(const char **fmt, bool parse)
{
	int	res;

	res = 0;
	if (!parse)
		return (res);
	while (**fmt >= '0' && **fmt <= '9')
		res = res * 10 + *(*fmt)++ - '0';
	return (res);
}

/**
 * When given the order to parse (parse == true)
 * this function parses the characters after '%' and extracts
 * all information on how will we print the argument
 * it handles the flags ('0','-','+',' ', '#'), the width
 * the precision, the specifier and it increments the format pointer
 * along the way.
 * Otherwise (when parse = false) it gets the specifier directly.
 */
void	get_arg_data(t_arg_data *data, const char **fmt, bool parse)
{
	char	c;

	(*fmt)++;
	data_init(data);
	while (is_flag(**fmt) && parse)
	{
		c = *(*fmt)++;
		if (c == '0')
			data->flags |= ZERO_PAD;
		else if (c == '-')
			data->flags |= LEFT_JUSTIFY;
		else if (c == '#')
			data->flags |= HASH;
		else if (c == ' ' && !(data->flags & PLUS))
			data->flags |= SPACE;
		else if (c == '+')
			data->flags |= PLUS;
	}
	data->width = fmt_atoi(fmt, parse);
	if (**fmt == '.' && parse)
	{
		(*fmt)++;
		data->precision = fmt_atoi(fmt, parse);
	}
	data->specifier = **fmt;
}
