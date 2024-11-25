#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024 //Tamaño máximo que puede tener un input
#define MAX_ARGS 64 //Cantidad máxima de argumentos
#define SEPARATORS " \t\n" //Separador de argumentos (espacio, tabulación, nueva línea)

void execute(char **args) {
    int i = 0;
    
    // Iterar sobre cada argumento y ejecutar cada uno en un proceso separado
    while (args[i] != NULL) {
        pid_t pid = fork(); // Crear un proceso hijo para cada comando
        if (pid < 0) {
            perror("fork failed");
            return;
        }

        if (pid == 0) {
            // Proceso hijo ejecuta el comando
            if (execvp(args[i], &args[i]) == -1) {
                perror("exec failed");
            }
            exit(1);  // Si falla, el hijo termina
        }
        // El proceso padre no espera, pasa al siguiente comando
        i++;
    }
}

int main() {
    char input[MAX_INPUT_SIZE]; //Se define input con el máximo de argumentos
    char *args[MAX_ARGS];  // Array para almacenar los argumentos

    while (1) {
        printf("myshell> ");
        
        // Leer entrada del usuario
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) { 
            break; // Detectar fin de archivo (Ctrl+D)
        }

        // Dividir la entrada en comandos por espacio
        int arg_count = 0;
        char *token = strtok(input, SEPARATORS);
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, SEPARATORS);
        }
        args[arg_count] = NULL; // Terminar la lista de argumentos

        if (arg_count == 0) {
            continue;  // Si no hay argumentos, volver a pedir entrada
        }

        // Comprobar si el comando es 'exit'
        if (strcmp(args[0], "exit") == 0) {
            exit(0); // Terminar la shell
        }

        // Ejecutar los comandos en paralelo
        execute(args);
        
    }

    return 0;
}
