#include <stdio.h>
#include <sys/types.h>
main()

{

    pid_t pid;
    int i, j=0;

    for (i=1;i<4;i++)

    {

        if(fork()!=0){

            j--;

        }

        else{

            j++;

        }

        printf("PID: %d PPID: %d\n",getpid(),getppid());

    }
}
