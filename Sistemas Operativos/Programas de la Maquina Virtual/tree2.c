// Comando tree ver.2
#include <string.h> 
#include <sys/stat.h> 
#include <dirent.h> 
#include <stdlib.h> 
#include <stdio.h> 

void printdir(char *dir, int tam) 
{ 
    DIR *dp; 
    struct dirent *entrada; 
    struct stat statbuf; 
    if((dp = opendir(dir)) == NULL) { 
        fprintf(stderr,"No se puede abrir el directorio: %s\n", dir); 
        return; 
    } 
    chdir(dir); 
    while((entrada = readdir(dp)) != NULL) { 
        lstat(entrada->d_name,&statbuf); 
        if(S_ISDIR(statbuf.st_mode)) { 
            /* Encuentra un directorio*/ 
            if(strcmp(".",entrada->d_name) == 0 || 
                 strcmp("..",entrada->d_name) == 0) 
                 continue; 
            printf("%*s%s/\n",tam,"",entrada->d_name); 
           
	 /* Va hacia  un nuevo nivel */ 
            printdir(entrada->d_name,tam+4); 
        } 
        else printf("%*s%s\n",tam,"",entrada->d_name); 
    } 
    chdir(".."); 
    closedir(dp); 
} 

int main(int argc, char* argv[]) 

{ 
    char ruta[100];
    printf("Escribe una ruta:");
    scanf("%s",ruta);
   
    printf("done.\n"); 
    exit(0); 
}
