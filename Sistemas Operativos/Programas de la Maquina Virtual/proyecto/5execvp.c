/*
p busca la ruta del programa
l parametros separados por comas
v parametros pasados como vector
e variables de entorno pasadas como vector
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
pid_t pid;
int e,i;

char *arg1[30];

	 for(i=1;i<=argc;i++)
	 {
	 	arg1[i]=argv[i];
	 	printf("Argumento %d %s\n",i, arg1[i]);
	 }	
	 	
	pid=fork();

	if(pid==0){
		execlp(arg1[1], arg1[1],arg1[2],arg1[3],arg1[4]);
		perror("execl fallo al intentar ejecutar ls");
	}
	else{
		wait(&e);
		exit(1);
	}		
}
