/*
p busca la ruta del programa
l parametros separados por comas
v parametros pasados como vector
e variables de entorno pasados como vector
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

main() {
pid_t pid;
int e;

	system("clear");
	pid=fork();

	if(pid==0){
		printf("execl \n");
		execl("/bin/ls", "ls", "-l", "-F",(char *)0);
		perror("fallo al intentar ejecutar ls");
	}
	else{
		wait(&e);
		exit(1);
	}		
}
