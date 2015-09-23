#include <stdio.h>
#include <sys/types.h>
main(){
    pid_t pid;
    int i;
    for(i=0;i<2;i++){
        if(fork()==getpid())
        printf("UNAM");
        printf("PID: %d PPID: %d\n",getpid(),getppid());
    }
}



