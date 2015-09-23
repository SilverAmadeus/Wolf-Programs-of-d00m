#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_THREADS     5

pthread_t tabla_thr[MAX_THREADS];

typedef struct {
	int id;
  	char *cadena;
} thr_param_t;
thr_param_t param[MAX_THREADS];


funcion_thr(thr_param_t *p)
{
  	printf("%s %d\n", p->cadena, p->id);
	p->id=p->id+10;

  	pthread_exit(&(p->id));
}

main()
{
  	int i, *res;
  	for (i=0; i<MAX_THREADS; i++) 
	{
    		param[i].cadena = "Hola, soy el thread";
    		param[i].id     = i+1;
    		pthread_create(&tabla_thr[i], NULL, (void *)funcion_thr, &param[i]);
  	}

  	for (i=0; i<MAX_THREADS; i++) 
	{
    		pthread_join(tabla_thr[i], (void *)&res);
    		printf("El thread %d devolvio el valor %d\n", i, *res);
  	}


}
