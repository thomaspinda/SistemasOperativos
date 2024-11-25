#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct proc{
    char *nom[10];
    int id;
    struct proc *sig;
}nproc;

typedef nproc *puntero;

void insertar(puntero *cabeza, int e){
    puntero nuevo;
    nuevo = malloc(sizeof(nproc));
    nuevo -> id = e;
    nuevo -> sig = *cabeza;
    *cabeza = nuevo;
}
void imprimir(puntero cabeza){
    while(cabeza != NULL){
        printf(" %d\n", cabeza -> id);
        cabeza = cabeza -> sig;
    }
}
int main(){
    srand(time(NULL));
    int e;
    int i = 0;
    puntero cabeza;
    cabeza = NULL;
    while(i!=15){
        e = rand() % 1000+1;
        insertar(&cabeza, e);
        i++;
    }
    imprimir(cabeza);

    return 0;
}