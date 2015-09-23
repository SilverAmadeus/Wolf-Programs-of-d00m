/***
	Programa.modo.c
	Descripción Programa que muestra por pantalla la máscara de modo de un
	fichero o conjunto de ficheros.
***/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

main(int argc , char*argv[])
{
		struct stat estado;
		int i;
	
		if(argc < 2)
		{
			fprintf(stderr,"ERROR. Forma de uso: %s ficheros \n",
			argv[0]);
			//exit(-1);
		}
		
	for(i=1;i < argc;i++)
	{
		printf("%s:",argv[i]);
		if(lstat(argv[i],& estado ) == -1)
			perror(argv[i]);
		else
		{
			/*Calculo de la mascara de modo y permisos*/
			char permisos[]={'x','w','r'};
			char modo [10];
			int i;
			
			/*Permisos rwxrwxrwx*/
			for(i=0;i<9;i++)
				if(estado.st_mode & (1<<i) ) 
				modo[i] = permisos[i%3];
				else
					modo[i]='-';
			
			/*Tipo de fichero*/
			switch(estado.st_mode& S_IFMT)
			{
				case S_IFREG: /*Fichero ordinario*/
				modo[9]= '-';
				break;
				case S_IFDIR: /*Directorio*/
				modo[9]='d';
				break;
				case S_IFCHR: /*Dispositivo modo caracter*/
				modo[9]='c';
				break;
				case S_IFBLK: /*Dispositivo modo bloque*/
				modo[9]='b';
				break;
				case S_IFIFO: /*Tuberia con nombre*/
				modo[9]='b';
				break;
				case S_IFLNK: /*Enlace simbolico*/
				modo[9]='l';
				break;
				case S_IFSOCK: /*Conector(socket)*/
				modo[9]='s';
				break;
				default: /*Desconocido*/
				modo[9]='?';
				break;
			}
			/*Set elID del usuario*/
			if(estado.st_mode & S_ISUID)
				modo[6]='s';
			/*Set elID del grupo*/
			if(estado.st_mode & S_ISGID)
				modo[3]='s';
			/*Stiky Bit*/
			if(estado.st_mode & S_ISVTX)
				modo[0]='t';
			for(i=9;i>=0;i--)
				putchar(modo[i]);
			printf("\n");
		}
	}
	//exit(0);
}
