/***
	Programa: permisos.c
	Descripcion: este programa permite cambiar los permisos de un fichero o un
	conjunto de ficheros expresados con metacaracteres. Su forma de uso es:
	
		$ permisos rw-r--r-- fichero
		$ permisos rw-r--r-- *.c
		$ permisos rwxr-xr-x *.c
		
		Los permisos que no se indican en la mascara de especificacion de 
		permisos, no se modifican en el fichero.
		Por ejemplo:
		
		$permisos -xr-x *.c
		indica que la macara debe se: ****-xr-x. Es decir, los permisos de rwx del
		dueño y el permiso del grupo no cambian.
		
		Un asterico *** indica que ese permiso no debe cambiar.
		Por ejemplo:
		
		$permisos *wx---**x *.c
		El permiso de lectura para el dueño y los permisos de lectura y escritura
		para el resto de usuarios no deben cambiar
		
***/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

main(int argc, char *argv[])
{
	struct stat estado;
	mode_t permisos;
	mode_t activar = 0, desactivar = -1;
	int lon,i;
	
	if (argc < 3)
	{
		fprintf(stderr,"ERROR. Forma de uso: %s mascara ficheros\n",argv[0]);
		exit(-1);
	}
	
	/*Calculo de la mascara de permisos */
	lon = strlen(argv[1]);
	for(i=0;i<lon;i++)
	{
		char permisos[] ={'x','w','r'};
		
		if(argv[1][lon-1-i] == '*')
			continue;
		/*Permisos que se deben desactivar. */
		if(argv[1][lon-1-i] == '-')
			desactivar^=1<<i;
		/*Comprobacion de la sintaxis de la mascara*/
		else if( argv[1][lon-1-i] != permisos[i%3] )
			{
				fprintf(stderr,"ERROR. %s mascara incorrecta\n", argv[1]);
				exit(-1);
			}
		/**Permisos que se deben activar*/
		else
			activar |= 1<<i;
	}
	/*Fijacion de los permisos para cada fichero*/
	for(i=2;i<argc;i++)
	{
		if(stat(argv[i], &estado)==-1)
			perror(argv[i]);
		permisos=(estado.st_mode | activar) & desactivar;
		if(chmod(argv[i],permisos)==-1)
			perror(argv[i]);	
	}
	
}
