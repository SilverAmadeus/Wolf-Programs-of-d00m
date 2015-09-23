// Borrar carpetas con o sin archivos ver. 2.3
// Funcionando :)
#include <string.h> 
#include <sys/stat.h> 
#include <dirent.h> 
#include <stdlib.h> 
#include <stdio.h> 

void borrar(char *dir) 
{ 
    DIR *dp; 
    struct dirent *entrada; 
    struct stat statbuf; 
    
    rmdir(dir);
        		
    if((dp = opendir(dir)) == NULL) 
        return; 
     
    chdir(dir); 
    while((entrada = readdir(dp)) != NULL) 
    { 
    	lstat(entrada->d_name,&statbuf); 
        	if(S_ISDIR(statbuf.st_mode)) //pregunta 
        	{ 
            //Encuentra un directorio 
            if(strcmp(".",entrada->d_name) == 0 || strcmp("..",entrada->d_name) == 0) 
        		continue; 
        		if(rmdir(entrada->d_name) != 0)
            		borrar(entrada->d_name); //Llama de nuevo para borrar dir
        	} 
        	else remove(entrada->d_name); //borrar ficheros
    } 
    chdir(".."); 
    closedir(dp); 
    borrar(dir); //Llama de nuevo para borrar dir
} 

int main(int argc, char *argv[])
{
   // Analisis de los argumentos de la linea de ordenes
	if (argc < 2)
		fprintf (stderr, "Forma de uso: %s nombre_directorio. \n", argv [0]);
	else
   		borrar(argv[1]); 
}
