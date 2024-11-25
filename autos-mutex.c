#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 

// buffer 
int r=0, m=0, p=0, v=0, e=0;

// Mutex para exclusión mutua 
pthread_mutex_t mutex; 

// Función del productor 
void *productorR(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex); 
        if(r<4){
            r++;  
        
        printf("Se han fabricado %d ruedas.\n",r); 
        }

		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de producción 
	}
}
void *productorM(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex); 
        if(m<1){
            m++;  
             
        
        printf("Se ha fabricado %d motor.\n",m);
        }
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de producción 
	}
} 
void *productorP(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex); 
        if(p<4){
            p++;  
            
        printf("Se han fabricado %d puertas.\n",p); 
        }
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de producción 
	}
} 
void *productorV(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex); 
        if(v<6){
            v++;  
             
        
        printf("Se han fabricado %d ventanas.\n",v);
        }
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de producción 
	}
} 
void *productorE(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex); 
        if(e<3){
            e++;  
            
        
        printf("Se han fabricado %d espejos.\n",e); 
        }
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de producción 
	}
} 


// Función del consumidor 
void *consumidor(void *f) { 
	while (1) { 
		pthread_mutex_lock(&mutex);
		if(r==4 && m==1 && p==4 && v==6 && e==3){
            r=0;
            m=0;
            p=0;
            v=0;
            e=0;
            printf("Se ha ensamblado un automovil VROOOOOOOOOOOM \n");
        }
		pthread_mutex_unlock(&mutex); 
		sleep(1); // Simular tiempo de consumo 
	} 
} 

int main() { 
	pthread_t prod, cons;
	// Inicializar mutex 
	pthread_mutex_init(&mutex, NULL); 
	// Crear hilos para productor
	pthread_create(&prod, NULL, productorR, NULL);
	pthread_create(&prod, NULL, productorM, NULL); 
	pthread_create(&prod, NULL, productorP, NULL); 
	pthread_create(&prod, NULL, productorV, NULL); 
	pthread_create(&prod, NULL, productorE, NULL); 

	
	// Crear el hilo consumidor 
	pthread_create(&cons, NULL, consumidor, NULL); 
	// Esperar a que los hilos terminen (en este caso, no terminan) 
	pthread_join(prod, NULL); 
	pthread_join(cons, NULL); 
	// Destruir mutex 
	pthread_mutex_destroy(&mutex); 
	return 0; 
}
