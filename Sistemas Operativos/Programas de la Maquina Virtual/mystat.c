// Mi comando stat -x
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
    printf("  File: \"%s\"\n", argv[1]);
   
    //Tamaño del fichero
	printf("  Size: %d", filestat.st_size);
	
	//Tipo de Fichero
	printf ("     FileType: "); 
	//Análisis del tipo de dispositivo. 
	switch (filestat.st_mode & S_IFMT) { 
	case S_IFREG:
		printf ("Regular File\n");
		break;
	case S_IFDIR:
		printf ("Directory\n"); 
		break; 
	case S_IFCHR:
		printf ("Character \n"); 
		break; 
	case S_IFBLK:
		printf ("Block\n"); 
		break; 
	case S_IFIFO:
		printf ("Fifo\n"); 
		break;
}
	//Presentación de los permisos de lectura, escritura y ejecución en la forma 
	//(0777/rwxrwxrwx)
printf ("  Mode: (0%o/", filestat.st_mode & 0777);
int i;
for (i = 0; i < 9; i++)
	if (filestat.st_mode & (0400 >> i))
		printf ("%c",permisos [(8-i)%3]);
	else
		printf("-");
printf(")");
//UID y GID
printf ("        Uid: (   %d/   ", filestat.st_uid);
if ((pw = getpwuid (filestat.st_uid))== NULL)
	printf("??? ) ");
else
	printf ( "%s)", pw->pw_name);
		
printf (" Gid: (   %d/   ", filestat.st_gid);
if ((gr = getgrgid (filestat.st_gid))== NULL)
	printf("??? ) ");
else
	printf ( "%s)\n", gr->gr_name);	
    
    //Dispositivo
	printf("Device: %d,%d",
	(filestat.st_dev & 0xff00) >> 8, filestat.st_dev & 0x00ff);
	
	//Numero de nodo-i
	printf ("   Inode: %d", filestat.st_ino); 
	
	//Numero de enlaces.
	printf ("   Links: %d\n", filestat.st_nlink);


//Presentacion de los numeros de dispositivo
switch (filestat.st_mode & S_IFMT){
case S_IFCHR:
case S_IFBLK:
	printf (" Numeros de dispositivo: %d, %d\n",
	(filestat.st_rdev & 0xff00) >> 8, filestat.st_rdev & 0x00ff);
}

//Fechas del fichero
printf("Access: %s",
	asctime (localtime (&filestat.st_atime)));
printf("Modify: %s",
	asctime (localtime (&filestat.st_mtime)));
printf("Change: %s",
	asctime (localtime (&filestat.st_ctime)));

    return 0;
}


