//Pruebas argumentos
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h> // Para getpwuid
#include <grp.h> // Para getgrid
#include <string.h>

char destino[30]="";
char origen[5]="";
char space[]=" ";
char fin[]="(char *)0";
	
int main(int argc, char *argv[])
{
	int i;
	pid_t pid;
	int e;
   // Analisis de los argumentos de la linea de ordenes
	
	for(i=0;i<argc;i++)
	{
		printf ("Parametro: %d %s \n",i, argv [i]);
		if(i != 0)
		{
		strcat(destino, strcpy(origen,argv[i]) );
		strcat(destino, strcpy(origen,space) );
		}
	}
	strcat(destino, strcpy(origen,fin) );
	printf("%s\n",destino);
	
	pid=fork();
	if(pid==0){
		printf("execvp \n");
		execvp("ls", destino);
		perror("execl fallo al intentar ejecutar ls");
	}
	else{
		wait(&e);
		exit(1);
	}	
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
		execlp("sh", "sh", "-c",orden, NULL);
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
