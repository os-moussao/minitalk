/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:04:57 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/30 22:38:54 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * This version of printf function handles
 * flags ('0', '-', '+', ' ', '#'), the width and the precision...
 * it passes 1 to print_format() as an order to parse the format string.
 */
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = print_format(format, ap, 1);
	va_end(ap);
	return (ret);
}
