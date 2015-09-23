// Mi comando ls -l
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
	//tipo de fichero
	switch (filestat.st_mode & S_IFMT) { 
	case S_IFREG:
		printf ("-");
		break;
	case S_IFDIR:
		printf ("d"); 
		break; 
	case S_IFCHR:
		printf ("c"); 
		break; 
	case S_IFBLK:
		printf ("b"); 
		break; 
	case S_IFIFO:
		printf ("f"); 
		break;
}
	//Presentación de los permisos de lectura, escritura y ejecución
	int i;
	for (i = 0; i < 9; i++)
	if (filestat.st_mode & (0400 >> i))
		printf ("%c",permisos [(8-i)%3]);
	else
		printf("-");
	//Ligas
	printf ("  %d", filestat.st_nlink);
	//UID y GID
	if ((pw = getpwuid (filestat.st_uid))== NULL)
		printf(" ???");
	else
	printf (" %s", pw->pw_name);
		if ((gr = getgrgid (filestat.st_gid))== NULL)
	printf("  ???");
		else
	printf ("  %s", gr->gr_name);
	
	//Tamaño del fichero
	printf(" %d", filestat.st_size);
	
	//Fecha de ultima modificacion
	struct tm *tm;
	char buf[200];
	tm =localtime(&filestat.st_mtime);
	strftime(buf, sizeof(buf), "%b %d %H:%M", tm);
	printf(" %s",buf);
	
	//nombre del fichero
	printf(" %s\n", argv[1]);
}
