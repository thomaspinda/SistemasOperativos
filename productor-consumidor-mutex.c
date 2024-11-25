#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 

// buffer 
int buffer = 0;

// Mutex para exclusión mutua 
pthread_mutex_t mutex; 

// Función del productor 
void *productor(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex); 
		buffer++; 
		printf("Se añade un elemento al buffer. Elementos del buffer: %d\n", buffer);
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de producción 
	}
} 

// Función del consumidor 
void *consumidor(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex);
		buffer --; 
		printf("Se elimina un elemento del buffer.\n");
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de consumo 
	} 
} 

int main() { 
	pthread_t prod, cons;
	// Inicializar mutex 
	pthread_mutex_init(&mutex, NULL); 
	// Crear hilos para productor
	pthread_create(&prod, NULL, productor, NULL); 
	
	// Crear el hilo consumidor 
	pthread_create(&cons, NULL, consumidor, NULL); 
	// Esperar a que los hilos terminen (en este caso, no terminan) 
	pthread_join(prod, NULL); 
	pthread_join(cons, NULL); 
	// Destruir mutex 
	pthread_mutex_destroy(&mutex); 
	return 0; 
}
