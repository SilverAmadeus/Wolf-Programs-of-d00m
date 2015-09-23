/**
* hilos.c
* 
*  ejemplo de hilos linux
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void Funcion_HILO1(void);
void Funcion_HILO2(void);

int h1 = 5, h2 = 15;

main(void)
{
	pthread_t thread1, thread2;

	printf("Ejemplo de Hilos en LINUX\n"); 

// creamos el primer
  if (pthread_create(&thread1, NULL, (void *) Funcion_HILO1, NULL) != 0)
	perror("pthread_create"), exit(1); 

// creamos el segundo hilo
  if (pthread_create(&thread2, NULL,(void *) Funcion_HILO2, NULL) != 0)
	perror("pthread_create"), exit(1); 

// esperamos que acabe  
  if (pthread_join(thread1, NULL) != 0)    
	perror("pthread_join"),exit(1);

  if (pthread_join(thread2, NULL) != 0)    
	perror("pthread_join"),exit(1);

printf("\nFin de operacion con HILOS!\a\n"); 

  return 0; 
}

// Funcion_HILO1
void Funcion_HILO1()
{
  int i;
  
  for (i = 0;  i < h1; i++) 
   printf("Thread 1, Contador: %d\n",i); 

}

// Funcion_HILO2
void Funcion_HILO2()
{
  int i;
  
  for (i = 0;  i < h2; i++) 
   printf("\t\t Thread 2, contador: %d\n",i); 

}
