/***
Programa 9.3: Uso de las tuberia por parte del interprete de rdenes (tuberia.c)
Forma de uso: $ tuberia programa 1 programa_2 
Esto es equivalente a: $ programa. 1 | programa.2
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

main(int argc, char *argv[]){
	
	int tuberia[2];
	int pid;
	/* Anisis de los argumentos de la lnea de rdenes. */
		if (argc < 3) {
		fprintf (stderr,"Forma de uso: 0s programa_l programa_2\n",argv[0]); 
		exit (-1);
		}
	/* Creación de la tuberia. */
		if (pipe (tuberia) == -1) { 
		perror (argv[0]); 
		exit (-1);
		}
	/* Creación de los procesos padre e hijo. */
		 if ((pid = fork O) == -1) { 
		 perror (argv[0] ); 
		 exit (-1) ;
			} else if (pid == 0) { /* Código del proceso hijo. */
		close (0);	
		dup (tuberia [0]);

		/* Al duplicar el descriptor asociado a tuberia[0], lo vamos a hacer sobre
		la primera entrada que haya libre en la tabla de descriptores de ficheros.
		 Esta entrada es la número 0, ya que antes hemos cerrado el fichero de 
		 entrada (descriptor 0). Asi, para el proceso hijo, el fichero estándar de 
		 entrada será el fichero asociado a la lectura de la tuberia, y todas las 
		 funciones que trabajen con el fichero estándar de entrada en realidad van
		 trabajar con el fichero de lectura de la tuberia. */ 
		 close (tuberia [0]); 
		 close (tuberia [1]);
		 
		/* Ejecución de programa_2. */
		execlp (argv [2], argv[2], 0);
		/* En la llamada a exec se heredan los descriptores asignados, por lo que
		el programa referenciado en argv [2] se ejecutará teniendo al fichero de 
		lectura de la tuberia como fichero estándar de entrada.*/
		} else { /* Código del proceso padre. */
	close (1);
	dup (tuberia [1]) ; 
	close (tuberia [0]); 
	close (tuberia [1]);

	/* Ejecución de programa_l. */
	 execlp (argv [1], argv[l] , 0);
	}
	exit (0);
}
