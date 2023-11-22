#include <stdio.h>

void desencriptar() {   
    unsigned dato = 0;
    FILE *archivo = NULL;
    FILE *nuevo = NULL;
  
    archivo = fopen("encriptado010.dat", "rb");
    nuevo = fopen("descifrado.txt", "wb");
    // for (int i = 0; i < 256; i++) {
    //     int n = 0;
    //     printf("=======%d======\n", i);    
    //     while (n < 50)
    //     {
    //         dato = fgetc(archivo);
    //         dato = (dato + i) % 256;
    //         printf("%c", dato);
    //         n++;
    //     }
    //     printf ("\n==========\n");
    //     fseek(archivo, 0, SEEK_SET);
    // }
  for (int i = 0; i < 3801; i++) {
            dato = fgetc(archivo);
            dato = (dato + 260) % 256;
            fputc(dato, nuevo);
        }

  
    fclose(archivo);
    fclose(nuevo);
    return;
}

int main() {
    printf("Desencriptado\n");
    desencriptar();


    return 0;
}