//Comando tree ver. 1
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

main(int argc, char *argv[])
{

	int i;
	if(argc < 2){
		printf("\nError. Forma de uso: %s directorio\n", argv[0]);
	return;
	}
	tree(argv[1]);
	return;
}

tree(char *ruta)
{
	
	DIR *dirp;
	struct dirent *dp;
	static nivel = 0;
	struct stat buf;
	char fichero[FILENAME_MAX];
	int i,ok;
	
	if((dirp = opendir(ruta)) == NULL){
		perror(ruta);
		return;
	}
	
	while ((dp = readdir (dirp)) != NULL) {
	if (EQ (dp->d_name, ".") || EQ (dp->d_name, ".."))
		continue;
	printf("%s/\n", dp->d_name);
	/* Lectura del nodo i del fichero. */
	ok = stat (fichero, &buf);
	/* Si el fichero es un subdirectorio, llamamos nuevamente a tree. */
	if (ok != -1 && (buf.st_mode & S_IFMT) == S_IFDIR) {
		for (i = 0; i < nivel; i++)
			printf ("\t");
		printf ("%s \n", dp->d_name);
		++nivel;
		tree (fichero);
		--nivel;	
	}
 }
}