/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:22:44 by omoussao          #+#    #+#             */
/*   Updated: 2021/12/31 18:22:22 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "printf/includes/ft_printf.h"

static int	is_w_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	i = 0;
	while (is_w_space(str[i]))
		i++;
	sign = 1 - (str[i] == '-') * 2;
	i += (str[i] == '+' || str[i] == '-');
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (sign * res);
}

void	send_char(int pid, char c)
{
	int		i;

	i = 8;
	while (i--)
	{
		kill(pid, 30 + (int)((c >> i) & 1));
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	int		pid;
	char	*s;

	if (ac != 3)
	{
		ft_printf("Usage: ./client [server PID] [string to send]\n");
		exit(1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		exit(1);
	s = av[2];
	while (*s)
		send_char(pid, *s++);
}
