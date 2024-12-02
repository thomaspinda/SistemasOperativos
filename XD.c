#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct proc {
    char nom[20];       // Arreglo para almacenar el nombre.
    int id;             // ID del proceso.
    struct proc *sig;   // Nodo siguiente.
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

// Inserta un nuevo nodo al inicio de la lista enlazada.
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

// Imprime la lista enlazada.
void imprimir(puntero cabeza) {
    while (cabeza != NULL) {
        printf("ID: %4d, %s\n", cabeza->id, cabeza->nom);
        cabeza = cabeza->sig;
    }
}

// Implementa el algoritmo FIFO para el manejo de páginas.
int fifo(puntero cabeza, int num_marcos) {
    int marcos[num_marcos]; // Array para almacenar los marcos.
    int fallos = 0;         // Contador de fallos de página.
    int indice = 0;         // Índice circular para reemplazo.

    // Inicializa los marcos con -1 (indicando que están vacíos).
    for (int i = 0; i < num_marcos; i++) {
        marcos[i] = -1;
    }

    while (cabeza != NULL) {
        int pagina = cabeza->id; // Página actual.
        int encontrada = 0;      // Bandera para verificar si la página ya está en los marcos.

        // Verifica si la página ya está en los marcos.
        for (int i = 0; i < num_marcos; i++) {
            if (marcos[i] == pagina) {
                encontrada = 1;
                
                break;
            }
            printf("%d ",marcos[i]);
        }

        if (!encontrada) {
            // Fallo de página: Reemplaza usando FIFO.
            marcos[indice] = pagina;
            indice = (indice + 1) % num_marcos; // Incrementa el índice de manera circular.
            fallos++;
        }

        cabeza = cabeza->sig; // Avanza al siguiente nodo.
    }
    printf("\n %d \n", fallos);
    return 0;
}

int main() {
    srand(time(NULL));
    int e;
    int i = 0;
    puntero cabeza;
    cabeza = NULL;

    // Genera 15 procesos con IDs aleatorios.
    while (i < 15) {
        e = rand() % 10 + 1;  // ID aleatorio entre 1 y 1000.

        // Inserta en la lista enlazada.
        insertar(&cabeza, e, i + 1);

        i++;
    }

    printf("Lista de procesos:\n");
    imprimir(cabeza);

    // Ejecuta el algoritmo FIFO con un número de marcos fijo.
    int num_marcos = 3; // Número de marcos disponibles.
    fifo(cabeza, num_marcos);

    return 0;
}
