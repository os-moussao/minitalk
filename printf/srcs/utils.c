/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:15:45 by omoussao          #+#    #+#             */
/*   Updated: 2021/12/01 13:08:13 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	max(int a, int b)
{
	return ((a > b) * a + (a <= b) * b);
}

int	min(int a, int b)
{
	return ((a < b) * a + (a >= b) * b);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = -1;
	while (++i < n)
		*(char *)(dest + i) = *(char *)(src + i);
	return (dest);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		*(char *)(b + i) = (unsigned char)c;
	return (b);
}

/**
 * This function rotates an array to the left by d elements
 * it is used with the flag LEFT_JUSTIFY
 */
void	left_rotate(char *arr, int size, int d)
{
	char	tmp;
	int		i;

	while (d--)
	{
		tmp = arr[0];
		i = 0;
		while (i + 1 < size)
		{
			arr[i] = arr[i + 1];
			i++;
		}
		arr[i] = tmp;
	}
}
