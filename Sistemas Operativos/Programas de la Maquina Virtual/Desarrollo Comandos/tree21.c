// Comando tree ver. 2.1
// Funcionando :)
              	//remove(entrada->d_name);
              	//rmdir(entrada->d_name);// Ya quedo borra archivo
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
    
    if((dp = opendir(dir)) == NULL) 
    { 
        fprintf(stderr,"No se puede abrir el directorio: %s\n", dir); 
        return; 
    }
     
    chdir(dir); 
    while((entrada = readdir(dp)) != NULL) 
    { 
    	lstat(entrada->d_name,&statbuf); 
        	if(S_ISDIR(statbuf.st_mode)) 
        	{ 
            //Encuentra un directorio 
            if(strcmp(".",entrada->d_name) == 0 || strcmp("..",entrada->d_name) == 0) 
        		continue; 
            printf("%*s%s/\n",tam,"",entrada->d_name); 
	 		//Va hacia  un nuevo nivel
            printdir(entrada->d_name,tam+4); //Llama de nuevo a la funcion
        	} 
        	else printf("%*s%s\n",tam-1,"",entrada->d_name); 
    } 
    chdir(".."); 
    closedir(dp); 
} 

int main(int argc, char *argv[])
{
   // Analisis de los argumentos de la linea de ordenes
	if (argc < 2)
		fprintf (stderr, "Forma de uso: %s nombre_directorio. \n", argv [0]);
	else
   		printdir(argv[1], 1); 
}
