#include "printf/includes/ft_printf.h"
#include <signal.h>
#include <stdlib.h>

void handler(int num)
{
	write(STDOUT_FILENO, "I won't die!\n", 13);
}

void handler2(int num)
{
	write(STDOUT_FILENO, "New handler\n", 12);
}

void sfhandler(int n)
{
	write(STDOUT_FILENO, "seg fault!!!\n", 13);
}

typedef struct sigaction t_sa;

int main()
{
	int *p = NULL;
	t_sa sa, sa_new, sa_old;
	sa.sa_handler = handler;
	sa_new.sa_handler = handler2;

	//sigaction(SIGINT, &sa, NULL);
	sigaction(SIGINT, &sa_new, &sa_old);
	sigaction(SIGINT, &sa_old, NULL);
	
	ft_printf("%p\n", sa_old.sa_handler);
	//signal(SIGSEGV, sfhandler);
	/*
	*p = 42;
	signal(SIGINT, handler);
	signal(SIGTERM, handler);
	signal(SIGKILL, handler);
	signal(SIGSTOP, handler);
	signal(SIGQUIT, handler);
	*/
	while (1)
	{
		ft_printf("Wasting your cycles. %d\n", getpid());
		sleep(2);
	}
}
