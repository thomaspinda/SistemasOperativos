#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct proc {
    char nom[20];       // Arreglo para almacenar el nombre.
    int id;             // ID del proceso
    struct proc *sig;   // Nodo siguiente
} nproc;

typedef nproc *puntero;

// Busca si la ID ya existe en la lista y devuelve el nombre correspondiente.
// Si no existe, devuelve NULL.
char *buscar_nombre(puntero cabeza, int id_buscado) {
    while (cabeza != NULL) {
        if (cabeza->id == id_buscado) {
            return cabeza->nom;  // Devuelve el nombre asociado a la ID.
        }
        cabeza = cabeza->sig;
    }
    return NULL;  // ID no encontrada.
}

void insertar(puntero *cabeza, int e, int posicion) {
    puntero nuevo;
    nuevo = malloc(sizeof(nproc));

    // Busca si la ID ya existe.
    char *nombre_existente = buscar_nombre(*cabeza, e);
    if (nombre_existente != NULL) {
        // Si la ID ya existe, reutiliza el nombre asociado.
        strncpy(nuevo->nom, nombre_existente, sizeof(nuevo->nom) - 1);
        nuevo->nom[sizeof(nuevo->nom) - 1] = '\0';  // Asegura el terminador nulo.
    } else {
        // Si la ID no existe, asigna un nuevo nombre.
        snprintf(nuevo->nom, sizeof(nuevo->nom), "Proceso %d", posicion);
    }

    nuevo->id = e;
    nuevo->sig = *cabeza;
    *cabeza = nuevo;
}

void imprimir(puntero cabeza) {
    while (cabeza != NULL) {
        printf("ID: %4d, %s\n", cabeza->id, cabeza->nom);
        cabeza = cabeza->sig;
    }
}


int main() {
    srand(time(NULL));
    int e;
    int i = 0;
    puntero cabeza;
    cabeza = NULL;
    int marco1[15];
    int marco2[15];
    int marco3[15];

    while (i < 15) {  // 15 iteraciones.
        e = rand() % 1000 + 1;  // ID aleatorio entre 1 y 1000

        // Inserta en la lista enlazada
        insertar(&cabeza, e, i + 1);

        // Almacena el ID en el array marco1

        marco1[i] = cabeza -> id;



        i++;
    }
    printf("Lista de procesos:\n");
    imprimir(cabeza);

    printf("\nIDs en el array marco1:\n");
    for (int i = 0; i < 15; i++) {
        printf("marco1[%d] = %d\n", i, marco1[i]);
    }
    return 0;
}
