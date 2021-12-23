/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:42:24 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/30 23:41:27 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * This funtion outputs the size of the absolute value
 * Ex: abs(-123) = 123, it will take 3 characters to print 123
 */
static int	get_size(unsigned long long abs, int precision, int radix)
{
	int	size;

	size = (!abs && !!precision);
	while (abs)
	{
		abs /= radix;
		size++;
	}
	return (size);
}

/**
 * This function updates all the data related to how will we print the
 * given number according to the standards of printf function.
 * For example: when the flag LEFT_JUSTIFY is on, the flag ZERO_PAD
 * should be ignored. Or when the value to print is a pointer the HASH
 * flag is on (meaning all pointers must have a "0x" prefix)
 * It also updates some number dimensions such as pad_size, radix...
 */
static void	update_data(t_arg_data *data, t_nbr_data *n_data)
{
	unsigned int	flags;
	char			sp;

	flags = data->flags;
	sp = data->specifier;
	if (sp == 'x' || sp == 'X' || sp == 'p' || n_data->nbr < 0)
		flags &= ~(SPACE | PLUS);
	if (data->precision >= 0 || flags & LEFT_JUSTIFY)
		flags &= ~ZERO_PAD;
	if (sp == 'd' || sp == 'i' || sp == 'u' || n_data->abs == 0)
		flags &= ~HASH;
	if (sp == 'p')
		flags |= HASH;
	data->flags = flags;
	n_data->sign = 0;
	if (sp == 'd' || sp == 'i' || sp == 'u')
		n_data->sign = '-' * (n_data->nbr < 0) + '+' * !!(flags & PLUS)
			+ ' ' * !!(flags & SPACE);
	n_data->radix = 10 + 6 * (sp == 'x' || sp == 'X' || sp == 'p');
	n_data->abs_size = get_size(n_data->abs, data->precision, n_data->radix);
	n_data->hash_prefix = 2 * !!(flags & HASH);
	n_data->nbr_size = max(n_data->abs_size, data->precision)
		+ !!n_data->sign + n_data->hash_prefix;
	n_data->size = max(n_data->nbr_size, data->width);
	n_data->pad_size = n_data->size - n_data->nbr_size;
}

/**
 * This function copies the absolute value
 * into the argument string
 */
static void	abs_itoa(char *arg, t_nbr_data n_data, t_arg_data data)
{
	int					i;
	int					radix;
	unsigned long long	abs;

	abs = n_data.abs;
	radix = n_data.radix;
	i = n_data.size - 1;
	if (abs == 0 && (data.precision != 0))
		arg[i] = '0';
	while (abs)
	{
		if (data.specifier == 'X')
			arg[i--] = UHEX[abs % radix];
		else
			arg[i--] = LHEX[abs % radix];
		abs /= radix;
	}
}

/**
 * This function copies the content to the argument string
 * according to the style specified int data and n_data
 */
static void	fill_arg(char *arg, t_arg_data data, t_nbr_data n_data)
{
	if (data.flags & ZERO_PAD)
	{
		ft_memset(arg, n_data.sign, !!n_data.sign);
		if (n_data.hash_prefix)
		{
			arg[0] = '0';
			arg[1] = 'x' - 32 * (data.specifier == 'X');
		}
		ft_memset(arg + !!n_data.sign + n_data.hash_prefix,
			'0', n_data.pad_size);
	}
	else
	{
		ft_memset(arg, ' ', n_data.pad_size);
		ft_memset(arg + n_data.pad_size, n_data.sign, !!n_data.sign);
		if (n_data.hash_prefix)
		{
			arg[n_data.pad_size] = '0';
			arg[n_data.pad_size + 1] = 'x' - 32 * (data.specifier == 'X');
		}
		if (data.precision > n_data.abs_size)
			ft_memset(arg + n_data.pad_size + !!n_data.sign
				+ n_data.hash_prefix, '0', data.precision - n_data.abs_size);
	}
	abs_itoa(arg, n_data, data);
}

/**
 * This function deal with all the numebrs (d, i, u, x, X, p)
 * it gets the number using the argument pointer
 * then it passes the values data (argument data) and n_data (number data)
 * to update_data(). After that it allocates memory for arg, applies the
 * LEFT_JUSTIFY flag if needed, writes the final result, frees the allocated
 * memory and quits.
 */
int	print_number(t_arg_data data, va_list ap)
{
	t_nbr_data	n_data;
	char		*arg;
	char		sp;

	sp = data.specifier;
	if (sp == 'd' || sp == 'i')
		n_data.nbr = va_arg(ap, int);
	else if (sp == 'u' || sp == 'x' || sp == 'X')
		n_data.nbr = va_arg(ap, unsigned int);
	else
		n_data.abs = (unsigned long)va_arg(ap, void *);
	if (sp != 'p')
		n_data.abs = n_data.nbr - 2 * (n_data.nbr < 0) * n_data.nbr;
	update_data(&data, &n_data);
	if (!n_data.size)
		return (n_data.size);
	arg = malloc(n_data.size);
	if (!arg)
		return (-1);
	fill_arg(arg, data, n_data);
	if (data.flags & LEFT_JUSTIFY)
		left_rotate(arg, n_data.size, n_data.pad_size);
	write(1, arg, n_data.size);
	free(arg);
	return (n_data.size);
}
