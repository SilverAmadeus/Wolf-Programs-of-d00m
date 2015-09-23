#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CAMINO 4096
int flag= 0,e,i,tam_min,tam_max,fin=0;
char modo1[10],nombre[256],tipoact[0],tipo[50],fecha[20],buf[20], *arg1[30];
pid_t pid;
struct tm *tm;

void recorrer_arbol (char *dir, void (*f)())
{
	DIR *directorio;
	struct dirent *entrada;
	struct stat estado;
	char camino [MAX_CAMINO];
	
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
		(*f) (camino, entrada, &estado);
		/* Determinación del tipo de fichero al que corresponde la entrada.Si se
		trata de un directorio, invocar a la función "recorrer_arbol"
		recursivamente. */
		if((estado.st_mode & S_IFMT) == S_IFDIR)
			recorrer_arbol(camino,f);
	}
	/*Cerrar e\ directorio.*/
	closedir(directorio);
}

void ejecuta(char *nombre)
{
	pid=fork();
	if(pid==0)
	{
		execlp(arg1[5], arg1[5],arg1[6],arg1[7],arg1[8],arg1[9],arg1[10]);
		perror("Fallo al ejecutar");
	}
	else
	{
		wait(&e);
	}		
}

void ejecutat(char *nombre)//Solo para busqueda por tamaño
{
	// for(i=4;i<=9;i++)
// 	{
// 		printf ("Parametro: %d %s \n",i,arg1[i]);
// 	}
// 	arg1[fin]=nombre;
	pid=fork();
	if(pid==0)
	{
		execlp(arg1[6], arg1[6],arg1[7],arg1[8],arg1[9],arg1[10],arg1[11]);
		perror("Fallo al ejecutar");
	}
	else
	{
		wait(&e);
	}		
}

void buscarp (char *camino, struct dirent *entrada, struct stat *estado)//Permisos
{
	/*Calculo de la mascara de modo y permisos*/
	char permisos[]={'x','w','r'},modo [10];
	int i;
	/*Permisos*/
	for(i=0;i<9;i++)
	{
		if(estado->st_mode & (1<<i) ) 
			modo[i] = permisos[i%3];
		else
			modo[i]='-';
		/*Set elID del usuario*/
			if(estado->st_mode & S_ISUID)
				modo[6]='s';
			/*Set elID del grupo*/
			if(estado->st_mode & S_ISGID)
				modo[3]='s';
			/*Stiky Bit*/
			if(estado->st_mode & S_ISVTX)
				modo[0]='t';
	}		
		if(0 == strncmp(modo1, modo, 8))
		{
			for(i=8;i>=0;i--)
				putchar(modo[i]);	
			printf (" %s \n", camino);
			if(flag == 1)
				ejecuta(camino);
		}
}

void buscarn (char *camino, struct dirent *entrada, struct stat *estado)//Nombre
{
	if(strcmp(nombre,entrada->d_name) == 0)
	{
		printf ("%s \n", camino);
		if(flag == 1)
				ejecuta(camino);
	}
}

void buscara (char *camino, struct dirent *entrada, struct stat *estado)//Tipo 
{
	switch(estado->st_mode & S_IFMT)
			{
				case S_IFREG: /*Fichero ordinario*/
				tipoact[0]= '-';
				break;
				case S_IFDIR: /*Directorio*/
				tipoact[0]='d';
				break;
				case S_IFCHR: /*Dispositivo modo caracter*/
				tipoact[0]='c';
				break;
				case S_IFBLK: /*Dispositivo modo bloque*/
				tipoact[0]='b';
				break;
				case S_IFIFO: /*Tuberia con nombre*/
				tipoact[0]='p';
				break;
				case S_IFLNK: /*Enlace simbolico*/
				tipoact[0]='l';
				break;
				case S_IFSOCK: /*Conector(socket)*/
				tipoact[0]='s';
				break;
				default: /*Desconocido*/
				tipoact[0]='?';
				break;
			}	
		if(strcmp(tipoact,tipo) == 0)
		{	
			printf("%s %s\n", tipoact, camino);
			if(flag == 1)
				ejecuta(camino);
		}
}

void buscarat (char *camino, struct dirent *entrada, struct stat *estado)//Ultimo Acces
{
	tm = localtime(&estado->st_atime);// time of last access
	strftime(buf, sizeof(buf), "%b %d", tm);
		if(strcmp(buf,fecha) == 0)
		{
			printf("%s %s\n",buf, camino);
			if(flag == 1)
				ejecuta(camino);
		}
}

void buscarmt (char *camino, struct dirent *entrada, struct stat *estado)//Ultima Modif
{
	//Fecha de ultima modificacion
	tm = localtime(&estado->st_mtime);// time of last modification
	strftime(buf, sizeof(buf), "%b %d", tm);
		if(strcmp(buf,fecha) == 0)
		{
			printf("%s %s\n",buf, camino);
			if(flag == 1)
				ejecuta(camino);
		}
}

void buscarct (char *camino, struct dirent *entrada, struct stat *estado)//Ultimo Cambi
{
	//Fecha de ultima modificacion
	tm = localtime(&estado->st_ctime);//time of last change
	strftime(buf, sizeof(buf), "%b %d", tm);
		if(strcmp(buf,fecha) == 0)
		{
			printf("%s %s\n",buf, camino);
			if(flag == 1)
				ejecuta(camino);
		}
}

void buscart (char *camino, struct dirent *entrada, struct stat *estado)//Tamaño
{
		if(estado->st_size >= tam_min && estado->st_size <= tam_max)
		{
			printf("%d", estado->st_size);
			printf(" %s\n",camino);
			if(flag == 1)
				ejecutat(camino);
		}
}

main (int argc,char *argv[])
{
	char tipobus[10],directorio[MAX_CAMINO];
	fin=argc;
	/*Analisis de los argumentos de la linea de órdenes.*/
	if(argc < 4)
		fprintf (stderr,"Error en argumentos\n");
	else
	{	
		if(argc > 5)
		{
				if( strcmp("ejecuta", argv[4]) == 0 )
				{
					flag = 1;
					for(i=5;i<argc;i++)
	 					arg1[i]=argv[i];
				}
				else if( strcmp("ejecuta", argv[5]) == 0 )
				{
					flag = 1;
					for(i=6;i<argc;i++)
	 					arg1[i]=argv[i];
				}
		}
		
		if( strcmp("a", argv[2]) == 0 )//Tipo Archivo
		{
			printf( "Busqueda por tipo de Archivo \n");
			strcpy(directorio,argv[1]);
			strcpy(tipo, argv[3]);
			recorrer_arbol(directorio, buscara);
		}
		
		if( strcmp("n", argv[2]) == 0 )//Busqueda Nombre
		{
			printf( "Busqueda por nombre \n");
			strcpy(directorio,argv[1]);
			strcpy(nombre, argv[3]);
			recorrer_arbol(directorio, buscarn);
		}
		
		if( strcmp("at", argv[2]) == 0 )//Fecha Ultimo Acceso
		{
			printf( "Ultimo Acceso \n");
			strcpy(directorio,argv[1]);
			strcpy(fecha, argv[3]);
			recorrer_arbol(directorio, buscarat);
		}
			
		if( strcmp("mt", argv[2]) == 0 )//Fecha Ultima Modificacion
		{
			printf( "Ultima Modificacion \n");
			strcpy(directorio,argv[1]);
			strcpy(fecha, argv[3]);
			recorrer_arbol(directorio, buscarmt);
		}
			
		if( strcmp("ct", argv[2]) == 0 )//Fecha Ultimo Cambio
		{
			printf( "Ultimo Cambio \n");
			strcpy(directorio,argv[1]);
			strcpy(fecha, argv[3]);
			recorrer_arbol(directorio, buscarct);
		}
		
		if( strcmp("p", argv[2]) == 0 )//Permisos
		{
			printf( "Busqueda por permisos \n");
			int i;
			char permisos[] ={'x','w','r'};
			int lon = strlen(argv[3]);
			
			for(i=0;i<lon;i++)
			{
				/*Comprobacion de la sintaxis de la mascara*/
				if(argv[3][lon-1-i] == '-')
				{
					modo1[i]='-';
					continue;
				}
				
				if(argv[3][lon-1-i] == 's')
				{
					modo1[i]='s';
					continue;
				}
				
				if(argv[3][lon-1-i] == 't')
				{
					modo1[i]='t';
					continue;
				}
				
				if( argv[3][lon-1-i] != permisos[i%3] )
				{
					fprintf(stderr,"ERROR. %s mascara incorrecta\n", argv[1]);
					exit(-1);
				}
				else
				modo1[i] = permisos[i%3];
			}
			strcpy(directorio,argv[1]);
			recorrer_arbol(directorio, buscarp);
		}
		
		if( strcmp("t", argv[2]) == 0 )//Tamanio
		{
			printf( "Busqueda por tamaño \n");
			strcpy(directorio,argv[1]);
			tam_min = atoi(argv[3]);
			tam_max = atoi(argv[4]);
			recorrer_arbol(directorio, buscart);
		}

	exit(0);
	}
	
}
