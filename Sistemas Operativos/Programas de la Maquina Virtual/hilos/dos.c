#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void haz_algo(void *);
void haz_algo_simple(void *);

//int h1=5, h2=2;


main(void)
{
  pthread_t thread1, thread2;

int h1=5, h2=2;
printf("vamos a ver...\n"); 

  if (pthread_create(&thread1, NULL, (void *) haz_algo, &h1) != 0)
	perror("pthread_create"), exit(1); 

  if (pthread_create(&thread2, NULL,(void *) haz_algo_simple, &h2) != 0)
	perror("pthread_create"), exit(1); 

 if (pthread_join(thread1, NULL) != 0)    
	perror("pthread_join"),exit(1);

 if (pthread_join(thread2, NULL) != 0)    
	perror("pthread_join"),exit(1);

printf("\nOK!\a\n"); 

  return 0; 
}

void haz_algo(void *arg)
{
int veces, i;
veces = *((int *)(arg));
 
  
  for (i = 0;  i < veces; i++) 
  {
   printf("Aqui, haciendo algo: %d\n",i); 
	fflush( stdin );
   sleep(2);
  }

}

void haz_algo_simple(void *arg)
{
  int i, veces;
veces = *((int *)(arg));
  
  for (i = 0;  i < veces; i++) 
  {   
	printf("Aqui, haciendo algo simple: %d\n",i); 
	sleep(2);
  }
}
