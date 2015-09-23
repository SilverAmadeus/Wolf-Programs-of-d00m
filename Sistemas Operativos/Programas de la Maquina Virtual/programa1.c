#include <stdio.h>
#include <sys/types.h>
main(){
    pid_t pid;
    int e,i;
    for(i=1;i<=3;i++)
    {
        if(fork()!=0)
            wait(&e);
        printf("PID: %d PPID: %d\n",getpid(),getppid());
        printf("%d\n",i);
    }
}
