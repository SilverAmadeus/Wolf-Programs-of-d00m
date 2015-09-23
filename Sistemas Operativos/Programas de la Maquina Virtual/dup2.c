/* dup2.c - Redirección usando dup2 */
/* Ejecuta el comando que se incluya como segundo argumento
redireccionando su salida estándar hacia el fichero de nombre
el primer argumento */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main (int contargs, char *args[])
{
int desc_fich;
if (contargs < 3)
{
printf ("Formato: %s fichero comando [opciones].\n",args[0]);
exit (1);
}

printf ("Ejemplo de redirección.\n");
desc_fich = open (args[1], O_CREAT|O_TRUNC|O_WRONLY,0666);
if (desc_fich==-1)
exit(-1);

dup2 (desc_fich, STDOUT_FILENO); /* Redirige la salida estándar */
close (desc_fich); /* Cierra el descriptor, ya no es necesario */

execvp (args[2], &args[2]); /* Ejecuta comando */
exit (1);
}