#include<stdio.h>
#include<sys/types.h>

main()
{
	pid_t pid;
	system("clear");
	printf("L0\n pid = %d, ppid =%d\n",getpid(),getppid());
	fork();
	printf("L1\n pid = %d, ppid =%d\n",getpid(),getppid());
	fork();
	printf("Bye pid = %d, ppid =%d\n",getpid(),getppid());
}
