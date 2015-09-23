#include <stdio.h>
#include <sys/types.h>
main(){
    pid_t pid;
    int j,i;
    j=1;
    for(i=1;i<3;i++)
    {
    fork();
    printf("%d,%d\n",i,j);
    j++;
    printf("PID: %d PPID: %d\n",getpid(),getppid());
    }
}
