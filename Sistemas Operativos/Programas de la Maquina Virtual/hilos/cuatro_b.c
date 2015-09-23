/* Creamos MAX_THREAD threads que sacan por pantalla una cadena y su
   identificador
   Una vez terminan su ejecucion devuelven como resultado su identificador */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_THREADS     10

// tabla con los identificadores de los threads
pthread_t tabla_thr[MAX_THREADS];

// tipo de datos y tabla con los parametros 
typedef struct {
	int id;
  	char *cadena;
} thr_param_t;
thr_param_t param[MAX_THREADS];

// tenemos que crear una tabla para los parametros porque los pasamos por 
// referencia. Asi, si solo tuvieramos una variable para los parametros
// al modificar esta modificariamos todas las que habiamos pasado anteriormente
// porque los threads no se quedan con el valor sino con la direccion

void funcion_thr(thr_param_t *p)
{
	// Esta es la funcion que ejecutan los threads
	// como veis, no tiene mucho secreto...
  	printf("%s %d\n", p->cadena, p->id);

  	// una vez terminamos, devolvemos el valor
  	pthread_exit(&(p->id));
}

main()
{
  	int i, *res;

  	// creamos los threads
  	printf("Creando threads...\n");
  	for (i=0; i<MAX_THREADS; i++) 
	{
    		param[i].cadena = strdup("Hola, soy el thread");
//    		param[i].cadena = "Hola, soy el thread";

    		param[i].id     = i;
    		pthread_create(&tabla_thr[i], NULL, (void *)funcion_thr, (void *)&param[i]);
  	}

  	// esperamos que terminen los threads
  	printf("Threads creados. Esperando que terminen...\n");
  	for (i=0; i<MAX_THREADS; i++) 
	{
    		pthread_join(tabla_thr[i], (void *)&res);
    		printf("El thread %d devolvio el valor %d\n", i, *res);
  	}

  	// sacamos el mensajito y salimos del programa
  	printf("Todos los threads finalizados. Adios!\n");

}
