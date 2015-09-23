#include <stdio.h>
#include <sys/types.h>
main()
{
    pid_t pid;
int e,i;
    for(i=10;i>8;i--)
    {
        fork();
        printf("PID: %d PPID: %d\n",getpid(),getppid());
        if(fork()!=0)
        wait(&e);
        printf("%d\n",i);
        printf("PID: %d PPID: %d\n",getpid(),getppid());
    }
}
