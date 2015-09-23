/************************************************************************************

					*Sistemas operativos
					*Programa que realiza las funciones de un stat en línea de comandos
	
				************************************************************************************/
#include<sys/stat.h>
#include<stdio.h>

main(int argc, char *argv[])
{

    int i;
    struct stat buf;
    char *ptr;

    for (i = 1; i < argc; i++) 
    {
        printf("%s: ", argv[i]);
        if (lstat(argv[i], &buf) < 0) 
	{
	    perror("lstat error");
            continue;
        }
         if (S_ISREG(buf.st_mode))
            ptr = "regular";
         else if (S_ISDIR(buf.st_mode))
            ptr = "directorio";
         else if (S_ISCHR(buf.st_mode))
            ptr = "caracter especial";
         else if (S_ISBLK(buf.st_mode))
            ptr = "bloque especial";
         else if (S_ISFIFO(buf.st_mode))
            ptr = "fifo";
         else if (S_ISLNK(buf.st_mode))
            ptr = "liga simbolica";
         else if (S_ISSOCK(buf.st_mode))
            ptr = "socket";
         else
            ptr = "** modo desconocido **";
         
	printf("%s\n", ptr);
  }
}
