//Programa Modificado
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h> // Para getpwuid
#include <grp.h> // Para getgrid


char permisos [] = {'x', 'w', 'r'};

int main(int argc, char *argv[])
{
   // Analisis de los argumentos de la linea de ordenes
	if (argc < 2){
		fprintf (stderr, "Forma de uso: %s nombre_fichero. \n", argv [0]);
	}
	
	struct stat filestat;
	struct passwd *pw;
	struct group *gr;
	//comprobar stat
	if ( stat(argv[1], &filestat) == -1){
		perror (argv[1]);
	}
    //Fichero
    printf("Fichero: %s\n", argv[1]);
    //Dispositivo
	printf("Reside en el dispositivo: %d, %d\n",
	(filestat.st_dev & 0xff00) >> 8, filestat.st_dev & 0x00ff);
	//Numero de nodo-i
	printf (" Nro. de nodo-i: %d\n", filestat.st_ino); 
	//Tipo de Fichero
	printf (" Tipo: "); 
	//Análisis del tipo de dispositivo. 
	switch (filestat.st_mode & S_IFMT) { 
	case S_IFREG:
		printf ("ordinario.\n");
		break;
	case S_IFDIR:
		printf ("directorio.\n"); 
		break; 
	case S_IFCHR:
		printf ("especial modo carácter.\n"); 
		break; 
	case S_IFBLK:
		printf ("especial modo bloque.\n"); 
		break; 
	case S_IFIFO:
		printf ("FIFO.\n"); 
		break;
}
//Funcion que realiza
if (filestat.st_mode & S_ISUID)
	printf (" Cambiar el ID del propietario en ejecución.\n");
if (filestat.st_mode & S_ISGID)
	printf (" Cambiar el ID del grupo en ejecución.\n"); 
if (filestat.st_mode & S_ISVTX)
	printf (" Stiky bit activo.\n");
	
//Presentación de los permisos de lectura, escritura y ejecución en la forma 
//0777 rwxrwxrwx
printf (" Permisos: 0%o ", filestat.st_mode & 0777);
int i;
for (i = 0; i < 9; i++)
	if (filestat.st_mode & (0400 >> i))
		printf ("%c",permisos [(8-i)%3]);
	else
		printf("-");
printf("\n");

//Numero de enlaces.
printf (" Enlaces: %d\n", filestat.st_nlink);

//UID y GID
printf (" User ID: %d; Nombre: ", filestat.st_uid);
if ((pw = getpwuid (filestat.st_uid))== NULL)
	printf("???\n");
else
	printf ("%s\n", pw->pw_name);
		
printf (" Group ID: %d; Nombre: ", filestat.st_gid);
if ((gr = getgrgid (filestat.st_gid))== NULL)
	printf("???\n");
else
	printf ("%s\n", gr->gr_name);	
	
//Presentacion de los numeros de dispositivo
switch (filestat.st_mode & S_IFMT){
case S_IFCHR:
case S_IFBLK:
	printf (" Numeros de dispositivo: %d, %d\n",
	(filestat.st_rdev & 0xff00) >> 8, filestat.st_rdev & 0x00ff);
}

//Tamaño del fichero
printf("Longitud: %d bytes.\n", filestat.st_size);

//Fechas del fichero
printf("Ultimo acceso: %s",
	asctime (localtime (&filestat.st_atime)));
printf("Ultima modificacion: %s",
	asctime (localtime (&filestat.st_mtime)));
printf("Ultimo cambio de estado: %s",
	asctime (localtime (&filestat.st_ctime)));

    return 0;
}


