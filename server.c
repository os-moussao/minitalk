/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:24:25 by omoussao          #+#    #+#             */
/*   Updated: 2021/12/27 19:55:46 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "printf/includes/ft_printf.h"

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	c;
	static int	cnt;
	
	(void)ucontext;
	cnt++;
	c = (c << 1) | (sig&1);
	if (cnt == 8)
	{
		if (c)
			write(1, &c, 1);
		else
		{
			ft_printf("\n%d\n", info->si_pid);
			kill(SIGUSR1, info->si_pid);
			exit(1);
		}
		cnt = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("Process id: %d\n", getpid());
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while(1)
		sleep(1);
}
