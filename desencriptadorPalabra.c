#include <stdio.h>

int main()
{
    char palabraClave[256] = { 28, 245, 5 };
    char palabraNueva[256] = { ' ', 'c', 'n' };

    //char palabraClave[21] = { 208, 151, 240, 230, 156, 245, 228, 150, 146, 252, 255, 253, 142, '\0' };
    //char palabraNueva[21] = { 151, 243, 'T', 'S', 163, 'G', 'Q', 146, 'D', '1', '5', '2', 130, '\0' };
    //char palabraClave[256] = { 242, 223, 210, 211, 243, 226, 231, 238, 252, 255, 253, 240, 230, 245, 228, 237, 229, 233, 248, 146, 208, 151, 135, 142, 156, 150, 1, 2, '\0' };
    //char palabraNueva[256] = { 'C', ' ', '"', '"', 'E', '.', 'U', 'H', '1', '5', '2', 'T', 'S', 'G', 'Q', 'D', 'R', 'W', 'K', 237, 151, 243, 225, 233, 250, 241, '7', '8', '\0' };

    char caracter = 0; //Se declaran las variables de tipo char "palabraClave" y "caracter" que nos servirán para almacenar la palabra clave ingresada y cada caracter que se lea del archivo respectivamente
    int bandera = 0; //Se declara la variable de tipo entero "bandera" que nos servirá para indicar si el caracter extraído del archivo encriptado se encuentra en la palabra clave
    int j=0;

    FILE *encriptado = fopen("encriptado010.dat","r"); //Se abre el archivo encriptado en modo lectura
    FILE *desencriptado = fopen("PruebaManual.txt", "w"); //Se crea el archivo desencriptado

   // while( !feof(encriptado) )
    for (int i = 0; i < 7941; i++) { 
        caracter = fgetc(encriptado); //leo un caracter del archivo "descifrado"
        bandera = 0; //Se reincia la bandera a 0
            j=0;    //variable que guardara la posición (subíndice)  de "palabraClave" si bandera el caracter  leído de "descifrado"
            for( int i=0; palabraClave[i] != '\0' && bandera==0; i++ )
                if( palabraClave[i] == caracter )
                { 
                    bandera = 1; //Bandera = 1 detiene la búsqueda
                    j = palabraNueva[i]; //
                } //end if (palabraClave[i]==caracter)
            if(bandera==1)  //Si la bandera se puso en alto(cambio su caracter igual a cero(0) 
                                //al caracter igual a uno(1)
                fputc(j,desencriptado);     //Grabo en "F_palabraclave" la posición(subíndice)  d   "palabraClave" del caracter
                                            //  leído de "descifrado"  
            else
                fputc(caracter,desencriptado); //Grabo en "F_palabraclave" el caracter leído d "descifrado"  
            //fin if(bandera==1)
        }//fin while (!feof(encriptado)

    return 0;
}