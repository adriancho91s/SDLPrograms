#include <stdio.h>
#include <stdlib.h>

int main() {
    //Name of the file to read each byte like a number
    FILE* archivo_lectura = fopen("PruebaManual.txt", "rb");

    if (archivo_lectura == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    int c;
    for (int i = 0; i < 3802; i = i + 1) {
        c = fgetc(archivo_lectura);
        printf("%i, ", c);
    }

    fclose(archivo_lectura);
    return 0;
}