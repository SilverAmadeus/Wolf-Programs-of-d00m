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
char *env[] = { "TERM=xterm", (char *)0 };	
	
	pid=fork();
	if(pid==0){
		execle("/usr/bin/clear","clear", (char *)0,env);
	}
	else{
		wait(&e);
		exit(1);
	}		
}
/*
TERM, variable del shell
Contiene informacion sobre el tipo de terminal en uso, y lo utilizan 
muchos programas para efectuar en forma correcta sus funciones de entrada 
y salida.
*/
