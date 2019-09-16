/*
Andres Luisos Barbosa Carranza
313055407
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Todos los hilos van a tener acceso a este arreglo.
int arreglo[] = {1, 0, 0, 1, 1, 0};

//Arreglo que va a almacenar todo el resultado de las comparaciones
int arreglo_resultado[6];

//Hilo que sirve de barrera
pthread_mutex_t lock;

void creaCopia(){
	int i;
	for(i = 0; i < (sizeof(arreglo) / sizeof(int)); i++){
		arreglo_resultado[i] = arreglo[i];
	}
}

void *verificacion(void *arg){
	//Se inicia la barrera
	pthread_mutex_lock(&lock);

	int id_hilo = (int *) arg;

	if(id_hilo == 0){
		printf("Comenzando a verificar el hilo 0 en tiempo 0\n");
		
		if(arreglo_resultado[1] == 0){
			arreglo[0] = 1;
		} else{
			arreglo[0] = 0;
		}

		printf("Termino verificar el hilo 0 en tiempo 0\n");
	}

	if(id_hilo >= 1 && id_hilo <5){
		printf("Comenzando a verificar el hilo %d", id_hilo);
		printf(" en tiempo 0\n");
	
		if(arreglo_resultado[id_hilo-1] == arreglo_resultado[id_hilo+1]){
			arreglo[id_hilo] = 1;
		} else{
			arreglo[id_hilo] = 0;
		}

		printf("Termino verificar el hilo %d", id_hilo);
		printf(" en tiempo 0\n");
	}

	if(id_hilo == 5){
		printf("Comenzando a verificar el hilo 5 en tiempo 0\n");

		if(arreglo_resultado[4] == 0){
			arreglo[5] = 1;
		} else{
			arreglo[5] = 0;
		}

		printf("Termino verificar el hilo 5 en tiempo 0\n");
	}

	//Se abre la barrera
	pthread_mutex_unlock(&lock);
}

int main(){
	int i;
	int j;

	//Se inicia el hilo mutex
	if (pthread_mutex_init(&lock, NULL) != 0){
        printf("\n Fallo la inicializacion del hilo mutex\n");
        return 1;
    }

    creaCopia();

	//Se van a tener 6 hilos, uno por cada posicion del arreglo
	pthread_t hilos[6];

	//Aqui se crean los hilos y se ejecutan cada uno con la funcion del tercer parametro
	//Cada funcion debe devolver un void y no recibe ningun parametro
	for(i=0; i < 6; i++){
		pthread_create(&(hilos[i]), NULL, verificacion, (int *) i);

		//Funcion que espera a que se termine la ejecucion del hilo
		//el segundo parametro es una variable que guarda el resultado esperado
		pthread_join(hilos[i], NULL);
	}
	
	printf("\nEl resultado es: ");

	for(j=0; j < 6; j++){
		printf("%d ", arreglo[j]);
	}

	printf("\n");

	//Se elimina el hilo mutex
	pthread_mutex_destroy(&lock);

}