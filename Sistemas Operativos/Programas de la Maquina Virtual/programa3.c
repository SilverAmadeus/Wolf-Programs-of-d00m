#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

main (){
    pid_t pid;
	int i,j=0;
	for(i=1;i<4;i++)
	{
	if(fork()==0){
            printf("PID: %d PPID: %d\n",getpid(),getppid());
		j++;
		      }
	else{
	     printf("PID: %d PPID: %d\n",getpid(),getppid());
		exit(1);
	}
j++;
}
}


