#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

// Semáforos para controlar productor y consumidor
sem_t sem_p, sem_c;

int r=0, m=0, p=0, v=0, e=0;

// Función para producir 
void *produceR(void *f) {
	while (1) { 
		sem_wait(&sem_p);
        if(r<4){
            r++;  
        }
        printf("Se han fabricado %d ruedas.\n",r); 

		sem_post(&sem_c); 
		sleep(1);
	} 
}
void *produceM(void *f) {
	while (1) { 
		sem_wait(&sem_p);
        if(m<1){
            m++;  
             
        }
        printf("Se ha fabricado %d motor.\n",m);
		sem_post(&sem_c); 
		sleep(1);
	} 
}
void *produceP(void *f) {
	while (1) { 
		sem_wait(&sem_p);
        if(p<4){
            p++;  
            
        }
        printf("Se han fabricado %d puertas.\n",p); 
		sem_post(&sem_c); 
		sleep(1);
	} 
}
void *produceV(void *f) {
	while (1) { 
		sem_wait(&sem_p);
        if(v<6){
            v++;  
             
        }
        printf("Se han fabricado %d ventanas.\n",v);
		sem_post(&sem_c); 
		sleep(1);
	} 
}
void *produceE(void *f) {
	while (1) { 
		sem_wait(&sem_p);
        if(e<3){
            e++;  
            
        }
        printf("Se han fabricado %d espejos.\n",e); 
		sem_post(&sem_c); 
		sleep(1);
	} 
}
// Función para consumir 
void *consume(void *arg) { 
	while (1) { //
		sem_wait(&sem_c); 
		if(r==4 && m==1 && p==4 && v==6 && e==3){
            r=0;
            m=0;
            p=0;
            v=0;
            e=0;
            printf("Se ha ensamblado un automovil VROOOOOOOOOOOM \n");
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
	pthread_create(&prod, NULL, produceR, NULL);
	pthread_create(&prod, NULL, produceM, NULL); 
	pthread_create(&prod, NULL, produceP, NULL); 
	pthread_create(&prod, NULL, produceV, NULL); 
	pthread_create(&prod, NULL, produceE, NULL); 

	pthread_create(&cons, NULL, consume, NULL); 
	// Esperar a que los hilos terminen (en este caso, no terminan) 
	pthread_join(prod, NULL); 
	pthread_join(cons, NULL); 
	// Destruir semáforos 
	sem_destroy(&sem_p); 
	sem_destroy(&sem_c);  
	return 0; 
}
