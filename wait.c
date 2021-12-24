// good tutorial: https://www.youtube.com/watch?v=tcYo6hipaSA
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int id = fork();
    int n, tmp;
    if (!id)
        n = 1;
    else
        n = 6, tmp = wait(NULL);

    for (int i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        fflush(stdout);
    }
    if (id)
        printf("\nChild pid: %d\nParent pid: %d\n", tmp, getpid());
}