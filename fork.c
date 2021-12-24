#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int id = fork();
	if (id)
		fork();
	printf("pid = %d	id = %d\n", getpid(), id);
}