#include <stdio.h>
#include <sys/types.h>
main(){
	pid_t pid;
	int i;
	int n=10;
	
	for(i=0;i<n;i++)
	{
		pid=fork();
		if(pid !=0)
			break;
		printf("\nEl Padre del proceso %d es %d\n",getpid(),getppid());
	}
}

