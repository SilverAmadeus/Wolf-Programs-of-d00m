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

main() {
pid_t pid;
int e;
char *arg[] = {"ls", "-F", "-l", (char *)0};

	system("clear");
	pid=fork();

	if(pid==0){
		printf("execvp \n");
		execvp("ls", arg);
		perror("execl fallo al intentar ejecutar ls");
	}
	else{
		wait(&e);
		exit(1);
	}		
}
