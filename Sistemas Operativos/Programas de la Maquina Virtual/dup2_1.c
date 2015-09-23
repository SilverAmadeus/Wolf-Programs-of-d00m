/* dup2.c - Redirección usando dup2 */
/* Ejecuta el comando que se incluya como segundo argumento
redireccionando su salida estándar hacia el fichero de nombre
el primer argumento */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define COMMAND1 "who"
#define COMMAND2 "wc"

int main ()
{
int desc_fich,e;
pid_t pid;

if ( (pid=fork()) == 0 )
{ // hijo
printf ("bandera0.\n");
desc_fich = open ("guarda1", O_CREAT|O_TRUNC|O_WRONLY,0666);
if (desc_fich==-1){
printf ("Bandera1\n");
exit(1);
}
dup2 (desc_fich,1); /* Redirige la salida estándar */
close (desc_fich); /* Cierra el descriptor, ya no es necesario */
execlp(COMMAND1, COMMAND1, NULL);
exit(1);
}
else
{ // padre
wait(&e);
printf ("Bandera3\n");
exit (1);
}
}