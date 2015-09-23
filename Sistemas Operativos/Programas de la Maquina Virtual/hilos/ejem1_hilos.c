#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
void *thread_function(void *arg) 
{
	int i;
  	for ( i=0; i<20; i++ ) 
	{
    		printf("%d: Thread dice hola!\n",i+1);
    		sleep(1);
	}
  	return NULL;
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
    		abort(); }
}
