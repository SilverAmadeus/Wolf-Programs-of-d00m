// Comando tree ver. 2.2
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
    
    if(rmdir(dir) != 0)
    	{
        	printf("Primer Error al borrar\n");
        }
        else
        	printf("Borrado UNO\n");  
            		
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
        		{
        			printf("Error al borrar %s\n",entrada->d_name);
            		printdir(entrada->d_name,tam+4); //Llama de nuevo para abrir new dir 
            	}
            	else
            		printf("Borrado %s\n",entrada->d_name);        	
        	} 
        	else remove(entrada->d_name); //printf("%*s%s\n",tam,"",entrada->d_name); 
    } 
    chdir(".."); 
    closedir(dp); 
    printf("Se cerro el directorio\n");
    printdir(dir,tam+4); //Llama de nuevo para abrir new dir 
} 

int main(int argc, char *argv[])
{
   // Analisis de los argumentos de la linea de ordenes
	if (argc < 2)
		fprintf (stderr, "Forma de uso: %s nombre_directorio. \n", argv [0]);
	else
   		printdir(argv[1], 1); 
}
