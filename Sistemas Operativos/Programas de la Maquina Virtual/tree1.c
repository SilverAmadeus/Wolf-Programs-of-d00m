//Comando tree ver. 1

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


main(int argc, char *argv[]){

	int i;
	if(argc < 2){
		printf("\nError. Forma de uso: %s directorio\n", argv[0]);
		system("exit");
	}
	for(i=1;i<argc;i++)
		//if(argv[i][0] != '-')
			tree(argv[i]);
}

tree(char *ruta){
	
	DIR *dirp;
	struct dirent *dp;
	static nivel = 0;
	struct stat buf;
	char fichero[256];
	int i;
	
	if((dirp = opendir(ruta)) == NULL){
		perror(ruta);
		return;
	}
	
	while((dp = readdir(dirp)) != NULL){
		printf(fichero, "%s/%s", ruta, dp->d_name);
		if((buf.st_mode & S_IFMT) == S_IFDIR){
			for(i=0;i<nivel;i++)
				printf("\t");
			printf("%s\n", dp->d_name);
			++nivel;
			tree(fichero);
			--nivel;
		}
		
	}
}