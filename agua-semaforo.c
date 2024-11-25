#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

// Semáforos para controlar productor y consumidor
sem_t sem_p, sem_c;

int h=0,o=0;

// Función para producir 
void *produceH(void *f) {
	while (1) { 
		sem_wait(&sem_p); // Esperar
        if(h<2){
        h++;
        }
		printf("Se ha producido %d de hidrogeno.\n",h); 

		// Señal de que hay elementos en el buffer
		sem_post(&sem_c); 
		sleep(1); // Simula el tiempo de producción
	} 
}
void *produceO(void *f) {
	while (1) { 
		sem_wait(&sem_p); 
        // Esperar 
        if(o<2){
        o++;
        }
		printf("Se ha producido %d de oxigeno.\n",o); 
		// Señal de que hay elementos en el buffer
		sem_post(&sem_c); 
		sleep(1); // Simula el tiempo de producción
	} 
}
// Función para consumir 
void *consume(void *arg) { 
	while (1) { //
		sem_wait(&sem_c);
        if(o==2 && h==2){
        h-=2;
        o-=2;
		printf("Se consume un elemento del buffer.\n"); 
        }
		// Permitir producir más elementos al buffer 
		sem_post(&sem_p); // Permitir producir 
		sleep(1); // Simula el tiempo de consumo 
	} 
} 

int main() { 
	pthread_t prod, cons; // Inicializar semáforos 
	sem_init(&sem_p, 0, 1); // Pueden producirse 1 elemento en el buffer 
	sem_init(&sem_c, 0, 0); // Inicialmente no hay elementos en el buffer 
	// Crear los hilos para los productores y el consumidor 
	pthread_create(&prod, NULL, produceH, NULL); 
	pthread_create(&prod, NULL, produceO, NULL); 

	pthread_create(&cons, NULL, consume, NULL); 
	// Esperar a que los hilos terminen (en este caso, no terminan) 
	pthread_join(prod, NULL); 
	pthread_join(cons, NULL); 
	// Destruir semáforos 
	sem_destroy(&sem_p); 
	sem_destroy(&sem_c);  
	return 0; 
}
