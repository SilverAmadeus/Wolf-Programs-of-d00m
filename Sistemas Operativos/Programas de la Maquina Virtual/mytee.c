#include <stdio.h>/*standard input-output header*/
#include <stdlib.h>/*standard library */
#include <unistd.h>/*Contro del procesos*/
#include <fcntl.h>/*file control options*/

int main(int contargs, char *args[])
{
int fd[2],fd1[2],fich;
pipe(fd);/* Creacion de la tuberia. */
pipe(fd1);/* Creacion de la tuberia. */

if (!fork()) {/* Creacion de los procesos padre e hijo. */
fich = open (args[2], O_CREAT|O_TRUNC|O_WRONLY,0666);/* Creacion del archivo con sus 
argumentos */
dup2(fich,1);/* stdout es ahora fich */
close(fd[0]); /* fd[0] no se necesita */
execlp( args[1], args[1], NULL);/*se ejecuta el nuevo comando y la infomacion 
se guarda en fich*/
} 
else {
if(!fork()){/* Creacion de los procesos padre e hijo. */
dup2(fd1[1],1);/* stdout es ahora fd1[1] */
close(fd1[0]); /* fd1[0] no se necesita */
execlp("cat", "cat", args[2], NULL);/*se ejecuta el nuevo comando se lee toda la 
informacion del fichero*/
}
else{
dup2(fd1[0],0);/* stdin es ahora fd1[0] */
close(fd1[1]); /* fd1[1] no se necesita */
execlp(args[3], args[3], "-l", NULL); /*la informacion se pasa al comando*/
}
}
}