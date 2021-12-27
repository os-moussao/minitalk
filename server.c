/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:24:25 by omoussao          #+#    #+#             */
/*   Updated: 2021/12/27 17:39:02 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "printf/includes/ft_printf.h"

void	handler(int sig)
{
	static char	c;
	static int	cnt;
	
	cnt++;
	c = (c << 1) | (sig&1);
	if (cnt == 8)
	{
		write(1, &c, 1);
		c = 0;
		cnt = 0;
	}
}

int	main(void)
{
	//char				*str;
	struct sigaction	sa;

	ft_printf("Process id: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while(1)
		sleep(1);
}
