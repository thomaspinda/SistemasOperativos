#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validar(const char *hexa) {
    for (int i = 0; i < strlen(hexa); i++) {
        if (!isxdigit(hexa[i])) {  // Verifica si el carácter no es hexadecimal
            return 0;  // Retorna 0 si se encuentra un carácter no válido
        }
    }
    return 1;  // Retorna 1 si todos los caracteres son válidos
}

int main() {
    char hexa[100];
    long dec;
    do {
        printf("Ingrese la dirección lógica: ");
        scanf("%99s", hexa);

        if (!validar(hexa)) {
            printf("Entrada inválida. Por favor ingrese solo dígitos hexadecimales (0-9, A-F).\n");
        }
    } while (!validar(hexa)); //Si el char ingresado pasa la validación, se avanzará al calculo

    dec = strtol(hexa, NULL, 16); //Calcula el valor ingresado de hexadecimal a decimal

    printf("La dirección física es: %ld\n", dec);

    return 0;
}
