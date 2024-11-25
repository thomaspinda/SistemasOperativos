#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 
 

// buffer 
int h = 0; 
int o = 0;

// Mutex para exclusión mutua 
pthread_mutex_t mutex; 

// Función del productor 
void *productorH(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex);
        if(h==0){
		h+=2; 
        }
		printf("Se añade un atomo de hidrogeno: %d\n", h);
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de producción 
	}
} 
void *productorO(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex); 
        if(o==0){
		o+=2; 
        }
		printf("Se añade un atomo de oxigeno: %d\n", o);
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de producción 
	}
} 
// Función del consumidor 
void *consumidor(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex);
        if(o==2 && o==2){
		    o-=2;   
            h-=2;
        }
		printf("Se creó agua oxigenada.\n");
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de consumo 
	} 
} 

int main() { 
	pthread_t prod, cons;
	// Inicializar mutex 
	pthread_mutex_init(&mutex, NULL); 
	// Crear hilos para productor
	pthread_create(&prod, NULL, productorH, NULL);
    pthread_create(&prod, NULL, productorO, NULL); 



	pthread_create(&cons, NULL, consumidor, NULL); 

	// Esperar a que los hilos terminen (en este caso, no terminan) 
	pthread_join(prod, NULL); 
	pthread_join(cons, NULL); 
    
	// Destruir mutex 
	pthread_mutex_destroy(&mutex); 
	return 0; 
}
