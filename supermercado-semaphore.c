#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

// Semáforos para controlar productor y consumidor
sem_t sem_p, sem_c;
int clientes = 0;
int a=0, c=0, v=0;
int agua, carne, veg;
void *produceA(void *f) {
	while (1) { 
		sem_wait(&sem_p); 
        if(a<20){
        a++;
        printf("Se produjo %d litros de agua \n", a);
        }
		sem_post(&sem_c); 
		sleep(1);
	} 
}
void *produceC(void *f) {
	while (1) { 
		sem_wait(&sem_p); 
        if(c<20){
        c++;
        printf("Se produjo %d kilos de carne \n", c);
        }
		sem_post(&sem_c); 
		sleep(1); 
	} 
}
void *produceV(void *f) {
	while (1) { 
		sem_wait(&sem_p);
        if(v<20){
        v++;
        printf("Se produjo %d kilos de vegetales \n", v);
        }
		sem_post(&sem_c); 
		sleep(1); 
	} 
} 

void *cliente(){
    clientes++;
    agua = rand() % 10;
    carne = rand() % 10;
    veg = rand() % 10;
    printf("El cliente %d quiere %d litros de agua, %d kilos de carne y %d kilos de vegetales \n", clientes, agua, carne, veg);

}
void *consume(void *arg) { 
    cliente();
	while (1) { 
		sem_wait(&sem_c);

        if (a>=agua && c>=carne && v>=veg){
            a -= agua;
            c -= carne;
            v -= veg;
            printf("El cliente %d se llevó %d litros de agua, %d kilos de carne, %d kilos de vegetales \n", clientes, agua, carne, veg);
            cliente();
        }

		sem_post(&sem_p); 
		sleep(1); 
	}
} 

int main() {
	pthread_t prod, cons; // Inicializar semáforos 
	sem_init(&sem_p, 0, 1); // Pueden producirse 1 elemento en el buffer 
	sem_init(&sem_c, 0, 0); // Inicialmente no hay elementos en el buffer 
	// Crear los hilos para los productores y el consumidor 
	pthread_create(&prod, NULL, produceA, NULL);
    pthread_create(&prod, NULL, produceC, NULL);
    pthread_create(&prod, NULL, produceV, NULL);

	pthread_create(&cons, NULL, consume, NULL); 
	// Esperar a que los hilos terminen (en este caso, no terminan)
	pthread_join(prod, NULL); 
	pthread_join(cons, NULL); 
	// Destruir semáforos 
	sem_destroy(&sem_p); 
	sem_destroy(&sem_c);  
	return 0; 
}
