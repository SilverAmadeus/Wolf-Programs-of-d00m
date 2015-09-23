				/************************************************************************************

					*Sistemas operativos
					*Programa que realiza las funciones de un stat en línea de comandos
	
				************************************************************************************/


#include<stdio.h>		//Entrada/salida estandar		
#include<stdlib.h>		//Para utilizar exit
#include<sys/stat.h>		//para manejar struct stat, las llamadas y macros relacionadas		
#include<unistd.h>		//Tipos y constantes simbolicas estandar
#include<time.h>		//Para usar las llamadas para las fechas y horas de creación, acceso y modificación

main(int argc, char **argv)					//La función recibe como argumento el nombre de un archivo
{

int dev1,dev2,sb;						//Variables para manejar el número de divice y el stiky bit
int up=0;							//Variable para guardar el número correspondiente a los permisos de usuario
int gp=0;							//Variable para guardar el número correspondiente a los permisos de grupo
int op=0;							//Variable para guardar el número correspondiente a los permisos de otros
struct stat buf;						//Declarando un variable del tipo struct stat
char per[]={'-','-','-','-','-','-','-','-','-','-','-'};	//Arreglo para guardar el tipo de permisos y archivo de manera entendible para el usuario
char *ptr;							//Apuntador para guardar el tipo de archivo

	if(stat(argv[1], &buf)==-1)				
	{
		perror(argv[1]);				//Si ocurre un error imprimimos en pantalla y salimos
		exit(-1);
	}

	else							//En caso contrario realizamos la sig. instrucciones
	{
	

/***************************************Tipo de archivo**************************************/
	
		if(S_ISREG(buf.st_mode))			//Usando una macro preguntamos si el archivo es de tipo ordinario
			ptr = "fichero regular";		//Si es así se guarda el la variable ptr un valor indicandolo
		else if(S_ISDIR(buf.st_mode))			//Preguntamos si es de tipo directorio
		{
			ptr = "directorio";			//Si es así guardamos en la variable ptr un valor que lo indica
			per[0]='d';				//Ponemos una 'd' en la casilla del arreglo per corresponiente a: tipo de archivo
		}
		else if(S_ISCHR(buf.st_mode))			//preguntamos si es de tipo Caracter especial
		{
			ptr = "caracter especial";		//Si es así indicamos en la variable ptr que es de este tipo
			per[0]='c';				//Y guardamos una 'c' en la casilla correspondiente de per
		}
		else if(S_ISBLK(buf.st_mode))			//Preguntamos si es de tipo Bloque especial
		{
			ptr = "bloque especial";		//Si es así indicamos en la variable ptr que es de este tipo
			per[0]='b';				//Y guardamos una 'b' en la casilla correspondiente
		}
		else if(S_ISFIFO(buf.st_mode))			//preguntamos si es de tipo fifo
		{
			ptr = "fifo";				//Si es así indicamos en la variable ptr que es de este tipo
			per[0]='p';				//Y guardamos una 'p' en la primera posicion del arreglo per 
		}
		else if(S_ISLNK(buf.st_mode))			//preguntamos si es de tipo liga
		{
			ptr = "liga simbolica";			//Si es así lo indicamos en la variable ptr
			per[0]='l';				//Y ponemos una 'l' en la primera posicion de arreglo per
		}
		else if(S_ISSOCK(buf.st_mode))			//preguntamos si es de tipo socket
		{
			ptr = "socket";				//si es así lo indicamos en la variable ptr
			per[0]='s';				//Y ponemos una 's' en el arreglo per
		}
		else						
			ptr = "desconocido";			//En caso contrario es un tipo de archivo desconocido

/********************************************************************************************/


/************************************Permisos de usuario*************************************/
	
		if(((S_IRWXU)&(buf.st_mode))==(S_IRWXU))		//Pregutamos si el usuario tiene todos los permisos
		{
			up=7;						//Si es así lo indicamos en la variable up
			per[1]='r'; per[2]='w'; per[3]='x';		//Y en las casillas correspondientes del arreglo per
		}
		else							//En caso contrario se preguntará uno por uno
		{
			if(((S_IRUSR)&(buf.st_mode))==(S_IRUSR))	//Tiene el permiso de lectura?
			{
				up=up+4;				//Si es así lo indicamos en la variable up sumando 4
				per[1]='r';				//Y en la casilla correspondiente del arreglo per
			}
			if(((S_IWUSR)&(buf.st_mode))==(S_IWUSR))	//Tiene permiso de escritura?
			{
				up=up+2;				//Si es así lo indicamos en la variable up sumando 2
				per[2]='w';				//Y guardando una w en la casilla correspondiente de arreglo per
			}
			if(((S_IXUSR)&(buf.st_mode))==(S_IXUSR))	//Tiene permiso de ejecución?
			{
				up=up+1;				//Si es así lo indicamos en la variable up sumando 1
				per[3]='x';				//Y guardando un x en la casilla correspondiente del arreglo per
			}
		}

/**********************************************************************************************/


/*************************************Permisos de grupo****************************************/

		if(((S_IRWXG)&(buf.st_mode))==(S_IRWXG))		//Pregutamos si el grupo tiene todos los permisos
		{
			gp=7;						//Si es así lo indicamos en la variable gp
			per[4]='r'; per[5]='w'; per[6]='x';		//Y en las casillas correspondientes del arreglo per
		}
		else							//En caso contrario se preguntará uno por uno
		{
			if(((S_IRGRP)&(buf.st_mode))==(S_IRGRP))	//Tiene el permiso de lectura?
			{
				gp=gp+4;				//Si es así lo indicamos en la variable gp sumando 4
				per[4]='r';				//Y en la casilla correspondiente del arreglo per
			}
			if(((S_IWGRP)&(buf.st_mode))==(S_IWGRP))	//Tiene permiso de escritura?
			{
				gp=gp+2;				//Si es así lo indicamos en la variable gp sumando 2
				per[5]='w';				//Y guardando una w en la casilla correspondiente de arreglo per
			}
			if(((S_IXGRP)&(buf.st_mode))==(S_IXGRP))	//Tiene permiso de ejecución?
			{
				gp=gp+1;				//Si es así lo indicamos en la variable gp sumando 1
				per[6]='x';				//Y guardando una x en la casilla correspondiente de arreglo per
			}
		}

/***********************************************************************************************/


/***************************************Permisos de otros***************************************/

		if(((S_IRWXO)&(buf.st_mode))==(S_IRWXO))		//Pregutamos si otros tiene todos los permisos
		{
			op=7;						//Si es así lo indicamos en la variable op
			per[7]='r'; per[8]='w'; per[9]='x';		//Y en las casillas correspondientes del arreglo per
		}
		else							//En caso contrario se preguntará uno por uno
		{
			if(((S_IROTH)&(buf.st_mode))==(S_IROTH))	//Tiene el permiso de lectura?
			{
				op=op+4;				//Si es así lo indicamos en la variable op sumando 4
				per[7]='r';				//Y en la casilla correspondiente del arreglo per
			}
			if(((S_IWOTH)&(buf.st_mode))==(S_IWOTH))	//Tiene el permiso de escritura?

			{
				op=op+2;				//Si es así lo indicamos en la variable op sumando 2
				per[8]='w';				//Y en la casilla correspondiente del arreglo per
			}
			if(((S_IXOTH)&(buf.st_mode))==(S_IXOTH))	//Tiene el permiso de ejecución?
			{
				op=op+1;				//Si es así lo indicamos en la variable op sumando 1
				per[9]='x';				//Y en la casilla correspondiente del arreglo per
			}
		}

/**************************************************************************************************/


/*************************************Estado del Stiky bit*****************************************/

		if((S_ISVTX)&(buf.st_mode))	//Preguntamos si el stiky bit está activo
		
			sb=1;			//Si es así ponemos un 1 en la variable sb	
		
		else
			sb=0;			//En caso contrario ponemos un 0

/**************************************************************************************************/
		

		dev1=buf.st_dev;		//Guardamos en dos variables diferentes el valor que retorna la llamada
		dev2=buf.st_dev;		//Una para imprimir en decimal y otra para imprimir en hexadecimal


/*****************************Imprimir todos los datos en pantalla********************************/

		printf("  File: %s",argv[1]);
		printf("\n  Size: %d\t\tBlocks: %d\t   IO Block: %d\t  %s",buf.st_size,buf.st_blocks,buf.st_blksize,ptr);
		printf("\nDevice: %xh/%dd \tInode: %d\t   Links: %d",dev1,dev2,buf.st_ino,buf.st_nlink);
		printf("\nAccess: (%d%d%d%d/%s)\tUid:( %d/  )\t\tGid( %d/  )",sb,up,gp,op,per,buf.st_uid,buf.st_gid);
		printf("\nAccess: %s",asctime(localtime(&buf.st_atime)));
		printf("Modify: %s",asctime(localtime(&buf.st_mtime)));
		printf("Change: %s",asctime(localtime(&buf.st_ctime)));

/*************************************************************************************************/
	}
}
