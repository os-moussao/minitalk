/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:54:39 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/30 22:39:11 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * This version of printf function does not handle
 * flags, nor the width or the precision... it passes
 * a 0 value to print_format() as an order not to parse
 * the format string.
 */
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = print_format(format, ap, 0);
	va_end(ap);
	return (ret);
}
