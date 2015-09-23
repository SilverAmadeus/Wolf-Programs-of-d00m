#include<stdio.h>
#include<sys/types.h>
main()
{
	pid_t pid;
	system("cleaar");
	pid=fork();

	if(pid==0)
		printf("Hola desde el hijo\n");
	else
		printf("Hola desde el padre\n");
}
