//Pruebas argumentos
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char destino[300]="";
char origen[30]="";
char space[]=" ";

int main(int argc, char *argv[])
{
	strcat(destino, strcpy(origen,argv[1]) );
	strcat(destino, strcpy(origen,space) );
	strcat(destino, strcpy(origen,argv[2]) );
	
	sistema(destino);
}

sistema (const char *orden)
{
	int pid, tty, estado, w;
	
	fflush(stdout);
	/* Apertura del terminal asociado al proceso. */
	if((tty = open ("/dev/tty", O_RDWR)) == -1)
	{
		perror ("sistema");
		return(-1);
	}
	if((pid=fork())==0)
	{
		/* Codigo proceso hijo.*/
		/* Reasignamos los ficheros estandar de entrada, salida y errores del proceso
		hijo para independizarlos de los procesos padre. */
		close(0); dup(tty);
		close(1); dup(tty);
		close(2); dup(tty);
		close(tty);
		/*Ejecucion de la orden deseada. El parametro -c le indica al interprete sh 
		que orden no es un fichero del órdenes para el interprete*/
		execlp("sh", "sh", "-c", orden, NULL);
		/*Codigo de salida en caso de que no se pueda ejecutar execlp.*/
		exit(127);
	}
	/* Codigo para el proceso padre.*/
	close(tty);
	/*Espera hasta que termine el proceso hijo.*/
	while((w = wait(&estado)) != pid && w != -1);
	/*El codigo que se recibe en estado es el de salida del programa sh. */
	if(w == -1)
		estado = -1;
	return estado;
}
