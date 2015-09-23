/***
	Programa: buscar.c
	Descripcion. Version simplificada del programa "find".
	Forma de uso:
	
	$ buscar fichero [donde]
	$ buscar gcc /usr
	/usr/bin/gcc
***/

#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

/*Constantes.*/

#define MAX_CAMINO 4096
/***
	Función: recorrer árbol
	Descripción. Función genérica para recorrer un árbol de directorios.
	Parámetros.
		char *dir; Nombre de la raíz del árbol que se va a recorrer.
		void (*f) ();Puntero a una función que realiza algun tratamiento con las
			entradas del directorio.
	Valor de retorno. Ninguno.
***/

void recorrer_arbol (char *dir, void (*f)())
{
	DIR *directorio;
	struct dirent *entrada;
	char camino [MAX_CAMINO];
	struct stat estado;
	
	/*Apertura del directorio.*/
	if((directorio = opendir (dir)) == NULL)
	{
		perror (dir);
		return;
	}

	/* Recorrido de las restantes entradas del directorio.*/
	while ((entrada = readdir (directorio))!= NULL)
	{
		/*Ignonar las entradas "." y ".."*/
		if(strcmp(entrada->d_name, ".") == 0 ||
			strcmp(entrada->d_name, "..") == 0 )
				continue;
		/* Formación del camino absoluto correspondiente a la entrada del
		directorio que se acabo de leer.*/
		sprintf(camino, "%s/%s", dir, entrada->d_name);
		/* Lectura del nodo-i correspondiente a la entrada.*/
		if (lstat (camino, &estado)== -1)
		{
			perror (camino);
			continue;
		}
		/* Procesamiento de la entrada con la función "f" */
		(*f) (camino,entrada->d_name);
		/* Determinación del tipo de fichero al que corresponde la entrada.Si se
		trata de un directorio, invocar a la función "recorrer_arbol"
		recursivamente. */
		if((estado.st_mode & S_IFMT) == S_IFDIR)
			recorrer_arbol(camino,f);
	}
	/*Cerrar e\ directorio.*/
	closedir(directorio);
}

char fbuscado [256];
buscar (char *camino, char *factual)
{
	if(strcmp(factual,fbuscado) == 0)
	printf ("%s \n", camino);
}

main (int argc,char **argv)
{
	char directorio [MAX_CAMINO];
	int i;

	/*Analisis de los argumentos de la linea de órdenes.*/
	if(argc < 2)
	{
		fprintf (stderr,"ERROR. Forma de uso: %s que [donde]\n", argv[0]);
		//exit(-1);
	}
	else if (argc < 3)
		strcpy(directorio, ".");
	else
		strcpy(directorio,argv [2]);
	strcpy(fbuscado, argv[1]);
		recorrer_arbol(directorio, buscar);
}
