#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

char *arg[] = {"ls", "-l", "proyecto.c", (char *)0};

void *thread_function(void *arg) 
{
	execvp("ls", arg);
	perror("execl fallo al intentar ejecutar ls");
}
main() 
{
	pthread_t mythread;
	
  	if ( pthread_create( &mythread, NULL, thread_function, NULL) ) 
	{
    	printf("error creating thread.");
    	abort();
  	}
  	if ( pthread_join ( mythread, NULL ) ) 
	{
    	printf("error joining thread.");
    	abort(); 
    }
}
