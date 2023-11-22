/*
╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║ ┌───────────────────────────────────────────────────────────────────────────────────────┬────────────────────────────────────────────────────────────────────────┐ ║
║ │ - Fecha de publicacion:                                                    26/05/2023 │                                                                        │ ║
║ │ - Hora:                                                                         07:00 │                                                                        │ ║
║ │ - Version del codigo:                                                           1.0.0 │                                                                        │ ║
║ │ - Autor:                                                 Ing(c) Santiago Torifa Manso │                                                                        │ ║
║ │ - Nombre del lenguaje utilizado:                                                    C │                                                                        │ ║
║ │ - Version del lenguaje utilizado:                                                 C17 │                           CREDITOS DEL CODIGO                          │ ║
║ │ - Versión del compilador utilizado:                                        gcc 12.2.0 │                                                                        │ ║
║ │ - Sistema Operativo sobre el que corre el programa    Windows 11 Home Single Language │                                                                        │ ║
║ │ - Presentado a:                                         Doctor Ricardo Moreno Laverde │                                                                        │ ║
║ ├───────────────────────────────────────────────────────────────────────────────────────┤                                                                        │ ║
║ │ - Universidad Tecnológica de Pereira                                                  │                                                                        │ ║
║ │ - Programa de Ingenieria de Sistemas y Computacion                                    │                                                                        │ ║
║ ├───────────────────────────────────────────────────────────────────────────────────────┴────────────────────────────────────────────────────────────────────────┤ ║
║ │                                                                                                                                                                │ ║
║ │ Proyecto Final: programa de archivos con registro de usuario y contraseña encriptada, ademas de una funcionalidad de graficar uan funcion polinomica que       │ ║
║ │                 pertenezca al usuario correspondiente o al administrador llamado usuario root                                                                  │ ║
║ │                                                                                                                                                                │ ║
║ └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘ ║
╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝*/


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <ctype.h>


#define Fuente "./font/arial.ttf"
#define letterSize 10


/** estructura para el manejo de usuarios:
  */
typedef struct Users {
  int ID;
  char Username[48];
  char Password[48];
} Users ;


/** tipado especial para poder almacenar punteros a funciones en un arreglo:
  */
typedef int (*MenuFunction)(Users* user, int result, int defaul);


/** estructura para manejar las opciones que elija el usuario: 
  */
typedef struct MenuOption {
    MenuFunction function;
    Users* nameUser;
    int result;
    int defaul;
} MenuOption ;


/** estructura para almacenar temporalmente la informacion de las graficas polinomicas:
  */
typedef struct Graphics {
  int UsernameID;
  char date[8];
  char function[30];
  int rangem;
  int rangeM;
  int incremt;
  int ID;
} Graphics ;


/** estructura para almacenar valores de 0 o 1 para saber si un cuadrante del plano se va a usar:
  */
typedef struct Quadrants {
  int quadrantsOne;
  int quadrantsTwo;
  int quadrantsThree;
  int quadrantsFourt;
} Quadrants;


/** estructura para almacenar los pixeles de proporcion que le pertenecen a los ejes,
  * donde el primer valor del arreglo corresponde a la proporcion superior en Y e izquierda en X,
  * y la segunda a la inferior en Y e derecha en X. Esta posicion depende de si es del eje x o y:
  */
typedef struct AxisSize {
  long long int xAxis[2];
  long long int yAxis[2];
} AxisSize ;


/** estructura para almacenar las coordenadas mas precisas del (0,0) que es la intersecion
  * entre los ejes X y Y :
  */
typedef struct CenterGraphic {
  long long int xCenter;
  long long int yCenter;
} CenterGraphic ;


/** estructura para almacenar todas las coordenadas, (los puntos) que se necesitan para crear la grafia
  * teniendo en cuenta el escalado del eje Y :
  */
typedef struct Point {
  long long int x;
  long long int y;
} Point ;


/** coordenadas de los ejes, numeros a los que corresponde :
  */
typedef struct CoordPlanes {
  long long int valueX;
  long long int valueY;
} CoordPlanes ;


// Estructura para almacenar temporalmente la informacion necesaria para crear una grafica
typedef struct GraphicInformation {
  Quadrants itsUsed;
  AxisSize axisSize;
  long long int intervalAxisX;
  long long int totalIntervalX;
  CenterGraphic center;
  Point point[10000];
  CoordPlanes coord[10000];
} GraphicInformation ;

int postMain();
int singInView();
int controlFirstSesion();
int optionMenuControl( Users* , int );
int validateOption( int , int, Users* );
int isInteger( const char* );
int getPassword( char*, int, int );
int obtainKeyWord( int );
int obtaindisplacement( );
void encrypt(char *, int);
int decrypt( char* );
int singIn( Users*, int );
int singInRootUser( Users*, int );
int createDataBase( Users*, int );
int createNewUser( Users*, int, int );
int assignUniqueID( int );
int assignUniqueReference( int );
int findUser( Users*, int );
Users findUserByRoot( Users* , int );
int findAllUsersByRoot( Users*, int, int );
int changePassword( Users* , int , int );
int changePasswordSelectAdmin( Users* , int , int );
int removeUser( Users*, int, int );
int compareDates(const char*, const char*);
void sortByDate(Graphics [], int );
void sortByDateDescending(Graphics [], int );
int createDbGraphics();
int createNewGraphic( Users*, int, int );
int findOneGraphic( Users* , int , int );
int findAllGraphics( Users* , int , int );
int viewAccessUser( Users* , int , int );
int viewAccessUsers( Users* , int , int  );
int printAccess( Users* , Graphics* , int , int );
int removeGraphic( Users* , int, int );
int separatedMonomios(char [30], char [10], int );
int fxValues(char [10], int );
int initGraphicate( Users* , int , int );
int viewGraphicFunction( Graphics* );
int controlValues( int [], int[] , int );
int selectGraphicPosible( GraphicInformation* , int [], int [], int [], int );
void quicksort(int[], int, int);
int partition(int [], int , int );
void swap(int* , int* );
void swapDate(Graphics* , Graphics* );
int validateQuadrants( GraphicInformation*, int [], int [],  int );
int obtainRatioAxis( GraphicInformation*, int [], int [], int, int );
int obtainZeroZero( GraphicInformation*, int [], int [], int, int );
int obtainCoordinates( GraphicInformation* , int [], int [], int [], int );
int graphicater(GraphicInformation *, int);
void drawFuction(SDL_Renderer *, TTF_Font *, CenterGraphic, Point[], int, CoordPlanes[], int );
void numbers(SDL_Renderer *, TTF_Font *, int, int, int);
int menuRootUser( Users* );
int menuNormalUser( Users* );
int handleRootUserOption ( Users*, int );
int handleNormalUserOption ( Users* , int );

void imprimirDatos(GraphicInformation *datos, int size) {
  printf("Datos de GraphicInformation:\n");
  printf("Quadrants:\n");
  printf("  QuadrantsOne: %d\n", datos->itsUsed.quadrantsOne);
  printf("  QuadrantsTwo: %d\n", datos->itsUsed.quadrantsTwo);
  printf("  QuadrantsThree: %d\n", datos->itsUsed.quadrantsThree);
  printf("  QuadrantsFour: %d\n", datos->itsUsed.quadrantsFourt);
  printf("AxisSize:\n");
  printf("  xAxis[0]: %lli\n", datos->axisSize.xAxis[0]);
  printf("  xAxis[1]: %lli\n", datos->axisSize.xAxis[1]);
  printf("  yAxis[0]: %lli\n", datos->axisSize.yAxis[0]);
  printf("  yAxis[1]: %lli\n", datos->axisSize.yAxis[1]);
  printf("CenterGraphic:\n");
  printf("  xCenter: %d\n", datos->center.xCenter);
  printf("  yCenter: %d\n", datos->center.yCenter);
  printf("Presione enter para avanzar\n");
  for (int i = 0; i < size; i++) {
    printf("  Coord %i - x: %lli, y: %lli\n", i + 1, datos->coord[i].valueX, datos->coord[i].valueY);
  }
  for (int i = 0; i < size; i++) {
    printf("  Punto %i - x: %lli, y: %lli\n", i + 1, datos->point[i].x, datos->point[i].y);
  }

  system("pause");
}


int main(int argc, char *argv[]) {
  postMain();
  system("cls");
  return 0;
};


/** se encarga de controlar que solo existan tres intentos de inicio de sesion
  * hasta que el programa decida cerrarce devido a que se han acabado los intentos,
  * ademas de validar si es la primera vez que se ejecuta el programa:
  * @return devuelve un 0 cuando haya finalizado el programa.
  */
int postMain() {
  Users singInUser;
  int option = -1; int attemps = 2; int validity = 1;
  int firtSesion = controlFirstSesion();

  while (validity) {
    int result = singIn(&singInUser, attemps);
    if (result) validity = 0;
    if (!attemps) return 0;
    attemps--;
  };

  if (!firtSesion) {
    printf("Usuario root creado correctamente\n");
    sleep(1);
    system("cls");
    return 0;
  };

  optionMenuControl(&singInUser, option);
  return 0;
}


/** se encarga de mostrar en la consola el titulo del aplicativo
  * y indicar que hay que ingresar el numbre de usuario:
  * @return devuelve un 0 al terminar su ejecución.
  */
int singInView() {
  printf("Aplicativo - Graficador - UTP\n");
  printf("Username: ");
  return 0;
};


/** se encarga de validar si la base de datos existe, ya que si esta existe significa
  * que ya existe un usuario root, por ende se puede dejar usar el aplicativo, 
  * de lo contrario se cerrara el programa apenas se cree el root:
  * @return devuelve un 0 si la base de datos no existe, devuelve un 1 si ya exite la misma.
  */
int controlFirstSesion() {
  FILE* database = fopen("database.txt", "r");

  if (!database) {
    return 0;
  }

  fclose(database);
  return 1;
}


/** se encarga de recibir la opcion que el usuario desea ejecutar, ademas de llamar
  * a otras funciones para poder mostrar el menu del usuario correspondiente:
  * @param user almacena la informacion del usuario correspondiente.
  * @param option almacena la opcion que el usuario va a elegir.
  * @return devuelve un cero cuando el usuario haya decedido finalizar
  * la ejecucion del programa.
  */
int optionMenuControl( Users* user, int option ) {
  while (option) {
    if (!strcmp(user->Username, "root")){
      menuRootUser(user);
    } else {
      menuNormalUser(user);
    }

    if (!strcmp(user->Username, "root")){
      option = validateOption(option, 7, user);
      if (option != 0){
        handleRootUserOption(user, option);
      }
    } else {
      option = validateOption(option, 5, user);
      if (option != 0){
        handleNormalUserOption(user, option);
      }
    }
  };
  return option;
};


/** se encarga de validar que las opciones que elija el usuario sean nuemeros enteros,
  * ademas de comprobar que esten en el rango correspondiente:
  * @param option  almacena la opcion que el usuario va a elegir.
  * @param userOption  almacena un numero para identificar que tipo de usuario se esta usando.
  * @param user alamcena la informacion del usuario que ha iniciado sesion.
  * @return devuelve la option que el usuario deseo ejecutar.
  */
int validateOption( int option, int userOption, Users* user ) {
  int validOption = 0;

  while (!validOption) {
    printf("Ingrese la opcion que desea ejecutar: ");

    char input[100];
    scanf("%s", input);


    if (isInteger(input)) {
      option = atoi(input);

      if (option >= 0 && option <= userOption) {
        validOption = 1;
      } else {
        printf("Opcion no valida.\n");
        sleep(1);
        system("cls");

        if (userOption == 7) {
          menuRootUser(user);
        }
        if (userOption == 5) {
          menuNormalUser(user);
        }
      }
    }
  }

  return option;
}


/** verifica si una cadena de caracteres representa un número entero válido.
  * @param str La cadena de caracteres a verificar.
  * @return 1 si la cadena representa un entero válido, 0 en caso contrario.
  */
int isInteger(const char* str) {
  if (*str == '+' || *str == '-')
    str++;

  while (*str != '\0') {
    if (!isdigit(*str))
      return 0;
    str++;
  }

  return 1;
}


/** Se encarga de ocultar la contraseña a la vista del usuario cuando este la este digitando:
  * @param password almacena un puntero con la direccion donde se guardara la contraseña.
  * @param maxLength almacena el total de caracteres maximos permitidos.
  * @param minLength almacena el minimo de caracteres permitidos.
  * @return devuelve un 1 si la contraseña se guardo correctamente, de lo contrario devuelve
  * 0 para indicar que el proceso no se ejecuto con exito.
  */
int getPassword(char* password, int maxLength, int minLength) {
  int i = 0;
  char ch;
  int finishRead = 0;

  while (i < maxLength - 1 && !finishRead) {
    ch = getch();

    if (ch == '\r') {
      if (i > minLength){
        password[i + 1] = '\0';
        finishRead = 1;
      }
    }
    
    if (ch == '\b' && i > 0 && !finishRead) {
      printf("\b \b");
      i--;
    }
    
    if (ch != '\b' && !finishRead) {
      printf("*");
      password[i] = ch;
      i++;
    }
  };

  system("cls");
  return (finishRead);
};


/** Se encarga de extraer la palabra clave del archivo seguridad.gra:
  * @param position la posicion del caracter que se va a extraer.
  * @return el caracter correspondiente a la posicion que se ingreso.
  */
int obtainKeyWord( int position ) {
  FILE* security = fopen("seguridad.gra", "r");
  char extractedChar = '-';
  int readStart = -1;

  if (!security){
    printf("Error, archivo no encontrado");
    return 0;
  }

  while ((extractedChar = fgetc(security)) != '-' && readStart != position){
    readStart++;
    if (position == readStart) {
      fclose(security);
      return extractedChar;
    }
  };
  fclose(security);
  return 0;
};


/** Se encarga de extraer el valor del desplazamiento del archivo seguridad.gra:
  * @return devuelve el numero entero correspondiente al desplazamiento del encriptado.
  */
int obtaindisplacement( ) {
  FILE* security = fopen("seguridad.gra", "r");

  if (!security){
    printf("Error, archivo no encontrado");
    return 0;
  }

  char line[11];

  while (fgets(line, sizeof(line), security)) {
    char* guion = strchr(line, '-');
    if (guion) {
      int numero;
      sscanf(guion + 1, "%d", &numero);
      fclose(security);
      return numero;
    }
  }

  fclose(security);
  return 0;
};


/** Se encarga de encriptar las contraseñas
  * antes de ser enviadas a la base de datos:
  * @param string {puntero} que contiene la direccion de memoria 
  * del string que contiene la palabra clave.
  * @return no devuelve nada pero cambia el contenido de la contraseña 
  * sustituyendola por una ya encriptada.
  */
void encrypt(char* string, int key) { 
  int lenghtPassword = strlen(string);
  char keyWord[7] = "";
  int displacement = obtaindisplacement();

  for (int i = 0; i < 7; i++) {
    keyWord[i] = obtainKeyWord(i);
  };

  int lenghKeyWord = strlen(keyWord);

  for (int i = 0; i < lenghtPassword; i++) {
    for (int j = 0; j < lenghKeyWord; j++){
      if (string[i] == keyWord[j]){
        string[i] = j + 32;
      }
    };
    string[i] = string[i] + displacement;
  };
};


/** Se encarga de decencriptar la contraseña para su manejo en este
  * programa:
  * @param {puntero} que contiene la direccion de memoria 
  * del string que contiene la palabra clave.
  * @return no devuelve nada pero la funcion se encarga de decencriptar
  * la contraseña de los usuarios.
  */
int decrypt( char* string ) {
  int lenghtPassword = strlen(string);
  char keyWord[7] = "";
  int displacement = obtaindisplacement();

  for (int i = 0; i < 7; i++) {
    keyWord[i] = obtainKeyWord(i);
  };

  int lenghKeyWord = strlen(keyWord);

  for (int i = 0; i < lenghtPassword; i++) {
    string[i] = string[i] - displacement;
    for (int j = 0; j < lenghKeyWord; j++){
      if (string[i] == j){
        string[i] = keyWord[j];
      }
    };
  };
};


/** Se encarga de ver si el usuario ingresado es el root o alguno distinto:
  * @param user almacena la información del usuario que se ingresa para iniciar sesion.
  * @param process almacena un valor sea 1 o 0 para saber como termino el proceso.
  * @return devuelve un dato entero process que define si la operacion de inicio de sesion se realizo
  * pudo realizar con exito o exitieron errores en el proceso.
  */
int singIn( Users* user, int process ) {
  singInView();
  fgets(user->Username, 48, stdin);
  user->Username[strlen(user->Username) - 1] = '\0';

  if (!strcmp(user->Username, "root")) {
    process = singInRootUser(user, 0);
    return process;
  }

  Users temp = findUserByRoot(user, 0);

  process = temp.ID;

  if (process) {
    process = findUser(user, 0);
  }

  return process;
};


/** Se encarga de verificar si existe el usuario root, de no existir, se crea
  * generando junto con el la base de datos, si el usuario existe este es buscado
  * rapidamente en el primer registro de la base de datos:
  * @param root almacena la informacion perteneciente al usuario root.
  * @param process almacena un valor sea 1 o 0 para saber como termino el proceso.
  * @return devuelve un dato entero process que define si la operacion de inicio de sesion se realizo
  * pudo realizar con exito o exitieron errores en el proceso.
  */
int singInRootUser( Users* root, int process ) {
  FILE* database = fopen("database.txt", "r");

  if (database) {
    fclose(database);

    process = findUser(root, 0);
    return process;
  }

  process = createDataBase(root, 0);
  return process;
};


/** Se encarga de crear la base de datos generando en ella un campo de ID,
  * otro de Username y otro de Password, posteriormente crea el usuario root
  * a partir de la informacion que haya ingresado el usuario:
  * @param root {Struct.Users} almacena la informacion perteneciente al usuario root.
  * @param result {Int} almacena un valor sea 1 o 0 para saber como termino el proceso.
  * @return devuelve un dato entero process que define si la operacion de inicio de sesion se realizo
  * pudo realizar con exito o exitieron errores en el proceso.
  */
int createDataBase( Users* root, int result ) {                                             
  FILE* database = fopen("database.txt", "w");

  if (!database) {
    printf("Error al crear la base de datos.\n");
    return 0;
  }

  char spacesUsername[48] = "", spacesPassword[48] = "";

  printf("Password: ");
  getPassword(root->Password, sizeof(root->Password), 3);
  int lengthPassword = strlen(root->Password);
  root->Password[lengthPassword - 1] = '\0';

  char *passwordAdrees = root->Password;

  encrypt(passwordAdrees);

  int lengthUsername = strlen(root->Username);
  while (lengthUsername < 48) {
    strcat(spacesUsername, " ");
    lengthUsername++;
  }
  
  while (lengthPassword < 48) {
    strcat(spacesPassword, " ");
    lengthPassword++;
  }

  root->ID = 1;

  fprintf(database, "------------------------------------------------------------------------------------------------------------------\n");
  fprintf(database, "- ID       - Username                                         - Password                                         -\n");
  fprintf(database, "------------------------------------------------------------------------------------------------------------------\n");

  fprintf(database, "- %i        - %s%s - %s%s -\n", root->ID, root->Username, spacesUsername, root->Password, spacesPassword);
  fprintf(database, "------------------------------------------------------------------------------------------------------------------\n");

  fclose(database);

  createDbGraphics();

  return 1;
}; 


/** Se encarga de permitirle al usuario root crear un nuevo usuario comun en la base de datos:
  * @param user almacena la informacion perteneciente al usuario que se desea crear.
  * @param process almacena un valor sea 1 o 0 para saber como termino el proceso.
  * @param defaul parametro extra que es tomado como un parametro no necesario.
  * @return devuelve un dato entero process que define si la operacion de inicio de sesion se realizo
  * pudo realizar con exito o exitieron errores en el proceso.
  */
int createNewUser( Users* root, int process, int defaul ) {
  FILE* database = fopen("database.txt", "a");
  Users user;

  if (!database) {
    printf("Error al crear la base de datos.\n");
    return 0;
  }

  printf("Aplicativo - Graficador - UTP\n");
  printf("Menu para el usuario: %s Crear nuevo usuario\n", root->Username);
  printf("Username: ");
  fflush(stdin);
  fgets(user.Username, 48, stdin);
  user.Username[strlen(user.Username) - 1] = '\0';

  char spacesUsername[48] = "", spacesPassword[48] = "";

  printf("Password: ");
  getPassword(user.Password, sizeof(user.Password), 3);
  int lengthPassword = strlen(user.Password);
  user.Password[lengthPassword] = '\0';

  char *passwordAdrees = user.Password;

  encrypt(passwordAdrees);

  int lengthUsername = strlen(user.Username);
  while (lengthUsername < 48) {
    strcat(spacesUsername, " ");
    lengthUsername++;
  }
  
  while (lengthPassword < 48) {
    strcat(spacesPassword, " ");
    lengthPassword++;
  }

  user.ID = assignUniqueID(0);

  if (user.ID < 10) {
    fprintf(database, "- %i        - %s%s - %s%s -\n", user.ID, user.Username, spacesUsername, user.Password, spacesPassword);
    fprintf(database, "------------------------------------------------------------------------------------------------------------------\n");
  }
  
  if (user.ID >= 10) {
    fprintf(database, "- %i       - %s%s - %s%s -\n", user.ID, user.Username, spacesUsername, user.Password, spacesPassword);
    fprintf(database, "------------------------------------------------------------------------------------------------------------------\n");
  }

  fclose(database);

  return process;
};


/** Se encarga de asignarle un ID unico a un registro de usuario, esto funciona
  * a partir de contrar cuantos usuarios existen ya en la base de datos:
  * @param generatedID contendra el ID que se le asignara al nuevo usuario.
  * @return devuelve un numero entero conrrespondiente al identificador unico que 
  * se le genero al nuevo usuario.
  */
int assignUniqueID( int generatedID ) {
  FILE *database = fopen("database.txt", "r");

  if (!database){
    printf("Error, archivo no encontrado");
    return 0;
  }
  
  int count = 0;
  char registerDb[116];

  while (fgets(registerDb, sizeof(registerDb), database)) {
    if (count > 3 && (count % 2) == 0) {
      generatedID++;
    }
    count++;
  }

  return generatedID + 1;
};


/** Se encarga de asignarle un valor de referencia a cada grafica, esto funciona
  * a partir de contar cuantos graficos existen y asi generarle una referencia unica:
  * @param generatedReference contendra el valor de regerencia que se le asignara
  * a la nueva grafica.
  * @return devuelve un numero entero conrrespondiente al identificador unico que 
  * se le genero a la nueva grafica.
  */
int assignUniqueReference( int generatedReference ) {
  FILE *graphicsDb = fopen("dbgraphics.txt", "r");

  if (!graphicsDb){
    printf("Error, archivo no encontrado");
    return 0;
  }
  
  int count = 0;
  char registerDb[132];

  while (fgets(registerDb, sizeof(registerDb), graphicsDb)) {
    if (count > 3 && (count % 2) == 0) {
      generatedReference++;
    }
    count++;
  }

  return generatedReference + 1;
}


/** Se encarga de abrir la base de datos y extraer de ella por cada iteracion de bucle
  * while un registro el cual contiene como información el ID, Username y Password del
  * usuario al que pertenece el registro, ya con estos datos se hara la comparacion para
  * saber si hemos encontrado al usuario indicado:
  * @param user almacena la informacion del usuario que se esta buscando.
  * @param result almacena un valor sea 1 o 0 para saber como termino el proceso.
  * @return devuelve un dato entero process que define si la operacion de inicio de sesion se realizo
  * pudo realizar con exito o exitieron errores en el proceso.
  */
int findUser( Users* user, int result ) {
  FILE *database = fopen("database.txt", "r");
  Users compareUser;

  if (!database){
    printf("Error, aun o se ha creado ningun usuario\n");
    return 0;
  }
  
  printf("Password: ");
  getPassword(user->Password, sizeof(user->Password), 3);
  user->Password[strlen(user->Password) - 1] = '\0';

  char *passwordAdrees = user->Password;

  encrypt(passwordAdrees);

  char registerDb[116];
  int lineWithData = 1;
  int lenghtUsername = strlen(user->Username);
  int lenghtPassword = strlen(user->Password);

  while (fgets(registerDb, sizeof(registerDb), database)) {
    if (lineWithData > 3 && (lineWithData % 2) == 0) {
      char formatString[50];

      sprintf(formatString, "- %%d - %%%ds - %%%ds -", lenghtUsername, lenghtPassword);
      sscanf(registerDb, formatString, &compareUser.ID, &compareUser.Username, &compareUser.Password);

      if (!strcmp(user->Username, compareUser.Username)) {
        if (!strcmp(user->Password, compareUser.Password)) {
          user->ID = compareUser.ID;
          system("cls");
          return  1;
        }
        printf("password incorrecta");
        sleep(1);
        system("cls");
        return 0;
      }
    };
    lineWithData++;
  };
  return 0;
};


/** Se encarga de abrir la base de datos y extraer de ella por cada iteracion de bucle
  * while un registro el cual contiene como información el ID, Username y Password del
  * usuario al que pertenece el registro, ya con estos datos se hara la comparacion para
  * saber si hemos encontrado al usuario indicado:
  * @param user almacena la informacion del usuario que se esta buscando.
  * @param result almacena un valor sea 1 o 0 para saber como termino el proceso.
  * @return devuelve un dato entero process que define si la operacion de inicio de sesion se realizo
  * pudo realizar con exito o exitieron errores en el proceso.
  */
Users findUserByRoot( Users* user, int result ) {
  FILE *database = fopen("database.txt", "r");
  Users compareUser;

  if (!database){
    printf("Error, aun no se ha creado ningun usuario\n");
  }

  char registerDb[116];
  int lineWithData = 1;

  while (fgets(registerDb, sizeof(registerDb), database)) {
    if (lineWithData > 3 && (lineWithData % 2) == 0) {
      char formatString[50];
      sscanf(registerDb, "- %i - %s ", &compareUser.ID, &compareUser.Username);

      if (!strcmp(user->Username, compareUser.Username) || user->ID == compareUser.ID) {
        user->ID = compareUser.ID;
        return *user;
      }
    };
    lineWithData++;
  };
  printf("El usuario no existe en la base de datos: ");
  sleep(2);
  system("cls");
  user->ID = 0;
  return *user;
}


/** Se encarga de hacer la busqueda de todos los usuarios para mostrar sus accesos
  * los cuales se listaran dependienfo de como lo haya pedido el usuario root: 
  * @param user almacena la informacion perteneciente al usuario que se desea crear.
  * @param process almacena un valor sea 1 o 0 para saber como termino el proceso.
  * @param defaul parametro extra que es tomado como un parametro no necesario.
  * @return devuelve un dato entero process que define si la operacion de inicio de sesion se realizo
  * pudo realizar con exito o exitieron errores en el proceso.
  */
int findAllUsersByRoot( Users* user, int result, int defaul ) {
  FILE *database = fopen("database.txt", "r");

  if (!database){
    printf("Error, aun o se ha creado ningun usuario\n");
    return 0;
  }

  char registerDb[116];
  int lineWithData = 1;

  while (fgets(registerDb, sizeof(registerDb), database)) {
    if (lineWithData > 5 && (lineWithData % 2) == 0) {
      Users userFind;
      sscanf(registerDb, "- %i - %s ", &userFind.ID, &userFind.Username);
      if (userFind.ID != 0) {
        printf("Username: %s\n\n", userFind.Username);
        findAllGraphics(&userFind, result, defaul);
      }
    };
    lineWithData++;
  };
  return result;
}


/** Se encarga de crear un nuevo registro con una grafica polinomica nueva que se generara con el
  * ID del usuario para que esta pertenezca a el:
  * @param user contiene la informacion del usuario actual.
  * @param result parametro extra obligatorios para poder llarmar la funcion.
  * @param defaul parametro extra obligatorios para poder llarmar la funcion.
  * @return devuelve un cero al finalizar su ejecucion.
  */
int changePassword( Users* user, int result, int defaul ) {
  FILE* database = fopen("database.txt", "r");
  Users password;
  Users nuevoPassword;
  Users repeatPassword;

  if (!database) {
    printf("Error al abrir el archivo de la base de datos.\n");
    return 0;
  }

  printf("Aplicativo - Graficador - UTP\n");
  printf("Menu para el usuario: %s Cambiar password\n", user->Username);
  printf("Password: ");
  getPassword(password.Password, sizeof(password.Password), 3);
  password.Password[strlen(password.Password) - 1] = '\0';

  encrypt(password.Password);

  if (strcmp(user->Password, password.Password)) {
    printf("password incorrecto");
    sleep(2);
    system("cls");
    return 0;
  }

  printf("Ingrese el nuevo password: ");
  getPassword(nuevoPassword.Password, 47, 3);
  nuevoPassword.Password[strlen(nuevoPassword.Password) - 1] = '\0';
  printf("Por favor ingrese nuevamente el mismo password: ");
  getPassword(repeatPassword.Password, 47, 3);
  repeatPassword.Password[strlen(repeatPassword.Password) - 1] = '\0';

  if (strcmp(nuevoPassword.Password, repeatPassword.Password)) {
    printf("password incorrecto");
    sleep(2);
    system("cls");
    return 0;
  }

  encrypt(nuevoPassword.Password);

  char registerDb[116] = "";
  char tempDataBase[10000] = "";
  int stopPrint = 1;
  int lineWithData = 1;
  
  char spacesUsername[48] = "", spacesPassword[48] = "";

  int lengthUsername = strlen(user->Username);
  int lengthPassword = strlen(nuevoPassword.Password);

  while (lengthUsername < 48) {
    strcat(spacesUsername, " ");
    lengthUsername++;
  }
  
  while (lengthPassword < 48) {
    strcat(spacesPassword, " ");
    lengthPassword++;
  }

  while (fgets(registerDb, sizeof(registerDb), database)) {
    char formatString[50];
    sprintf(formatString, "- %%d - %%%ds", lengthUsername);

    char username[48] = "";
    int usernameID = 0;
    sscanf(registerDb, formatString, &usernameID, &username); 

    if (lineWithData > 3 && (lineWithData % 2) == 0) {
      if (strcmp(user->Username, username)) {
        strcat(tempDataBase, registerDb);
        stopPrint++;
      } else {
        if (user->ID < 10) {
          char formatStringNew[50];
          strcat(nuevoPassword.Password, spacesPassword);
          sprintf(formatStringNew, "- %i        - %s%s - %s -\n", user->ID, user->Username, spacesUsername, nuevoPassword.Password);
          strcat(tempDataBase, formatStringNew);
          strcat(tempDataBase, "------------------------------------------------------------------------------------------------------------------\n");
        }
        if (user->ID >= 10) {
          char formatStringNew[50];
          strcat(nuevoPassword.Password, spacesPassword);
          sprintf(formatStringNew, "- %i        - %s%s - %s -\n", user->ID, user->Username, spacesUsername, nuevoPassword.Password);
          strcat(tempDataBase, formatStringNew);
          strcat(tempDataBase, "------------------------------------------------------------------------------------------------------------------\n");
        }
        stopPrint = 0;
      }
    };

    if (lineWithData == 2) {
      strcat(tempDataBase, "- ID       - Username                                         - Password                                         -\n");
    }

    if ((lineWithData % 2) == 1 && stopPrint){
      strcat(tempDataBase, "------------------------------------------------------------------------------------------------------------------\n");
    }
    lineWithData++;
  };
  fclose(database);

  FILE* newDataBase = fopen("database.txt", "w");

  if (!newDataBase) {
    printf("Error al abrir los archivos.\n");
    return 0;
  }

  fprintf(newDataBase, tempDataBase);

  fclose(newDataBase);

  return result;
}


/** Se encarga de eliminar un usuario de la base de datos creada en el archivo database.txt,
  * principalmente se asegura de salvar toda la informacion y luego eliminar el usuario:
  * @param root puntero con la informacion del usuario root.
  * @param result valor que sirve para definir la salida de la funcion
  * @param defaul parametro extra que es tomado como un parametro no necesario.
  * @return devuelve un numero entero conrrespondiente al identificador unico que 
  * se le genero al nuevo usuario.
  */
int changePasswordSelectAdmin( Users* root, int result, int defaul ) {
  FILE* database = fopen("database.txt", "r");

  if (!database) {
    printf("Error al abrir el archivo de la base de datos.\n");
    return 0;
  }

  Users user;
  Users compareUser;
  Users nuevoPassword;

  printf("Aplicativo - Graficador - UTP\n");
  printf("Menu para el usuario: %s cambiar password\n", root->Username);
  printf("Username: ");
  fflush(stdin);
  fgets(user.Username, sizeof(user.Username), stdin);
  user.Username[strlen(user.Username) - 1] = '\0';

  compareUser = findUserByRoot(&user, 0);

  if (strcmp(user.Username, compareUser.Username)) {
    printf("usuario no existente");
    sleep(1);
    system("cls");
    return 0;
  }

  printf("Ingrese su nueva password: ");
  getPassword(compareUser.Password, sizeof(compareUser.Password), 3);
  compareUser.Password[strcspn(compareUser.Password, "\n")] = '\0';
  printf("Por favor ingrese nuevamente el mismo password: ");
  getPassword(nuevoPassword.Password, sizeof(nuevoPassword.Password), 3);
  nuevoPassword.Password[strcspn(nuevoPassword.Password, "\n")] = '\0';

  if (strcmp(compareUser.Password, nuevoPassword.Password)) {
    printf("password incorrecto");
    sleep(2);
    system("cls");
    return 0;
  }

  encrypt(nuevoPassword.Password);

  char registerDb[116] = "";
  char tempDataBase[10000] = "";
  int stopPrint = 1;
  int lineWithData = 1;
  
  char spacesUsername[48] = "", spacesPassword[48] = "";

  int lengthUsername = strlen(compareUser.Username);
  int lengthPassword = strlen(nuevoPassword.Password);

  while (lengthUsername < 48) {
    strcat(spacesUsername, " ");
    lengthUsername++;
  }

  while (lengthPassword < 48) {
    strcat(spacesPassword, " ");
    lengthPassword++;
  }

  while (fgets(registerDb, sizeof(registerDb), database)) {
    char formatString[50];
    sprintf(formatString, "- %%d - %%%ds", lengthUsername);

    char username[48] = "";
    int usernameID = 0;
    sscanf(registerDb, formatString, &usernameID, &username); 

    if (lineWithData > 3 && (lineWithData % 2) == 0) {
      if (strcmp(compareUser.Username, username)) {
        strcat(tempDataBase, registerDb);
        stopPrint++;
      } else {
        if (compareUser.ID < 10) {
          char formatStringNew[30];
          strcat(nuevoPassword.Password, spacesPassword);
          sprintf(formatStringNew, "- %i        - %s%s - %s -\n", compareUser.ID, compareUser.Username, spacesUsername, nuevoPassword.Password);
          strcat(tempDataBase, formatStringNew);
          strcat(tempDataBase, "------------------------------------------------------------------------------------------------------------------\n");
        }
        if (compareUser.ID >= 10) {
          char formatStringNew[30];
          strcat(nuevoPassword.Password, spacesPassword);
          sprintf(formatStringNew, "- %i        - %s%s - %s -\n", compareUser.ID, compareUser.Username, spacesUsername, nuevoPassword.Password);
          strcat(tempDataBase, formatStringNew);
          strcat(tempDataBase, "------------------------------------------------------------------------------------------------------------------\n");
        }
        stopPrint = 0;
      }
    };

    if (lineWithData == 2) {
      strcat(tempDataBase, "- ID       - Username                                         - Password                                         -\n");
    }

    if ((lineWithData % 2) == 1 && stopPrint){
      strcat(tempDataBase, "------------------------------------------------------------------------------------------------------------------\n");
    }
    lineWithData++;
  };
  fclose(database);

  FILE* newDataBase = fopen("database.txt", "w");

  if (!newDataBase) {
    printf("Error al abrir los archivos.\n");
    return 0;
  }

  fprintf(newDataBase, tempDataBase);

  fclose(newDataBase);

  return result;
}


/** Se encarga de eliminar un usuario de la base de datos creada en el archivo database.txt,
  * principalmente se asegura de salvar toda la informacion y luego eliminar el usuario:
  * @param root puntero con la informacion del usuario root.
  * @param result valor que sirve para definir la salida de la funcion
  * @param defaul parametro extra que es tomado como un parametro no necesario.
  * @return devuelve un numero entero conrrespondiente al identificador unico que 
  * se le genero al nuevo usuario.
  */
int removeUser( Users* root, int result, int defaul ) {
  FILE* database = fopen("database.txt", "r");

  if (!database) {
    printf("Error al abrir el archivo de la base de datos.\n");
    return 0;
  }

  Users user;

  printf("Aplicativo - Graficador - UTP\n");
  printf("Menu para el usuario: %s Borra usuario\n", root->Username);
  printf("Username: ");
  fflush(stdin);
  fgets(user.Username, sizeof(user.Username), stdin);
  user.Username[strcspn(user.Username, "\n")] = '\0';

  char registerDb[116] = "";
  char tempDataBase[10000] = "";
  int stopPrint = 1;
  int lineWithData = 1;
  int lenghtUsername = strlen(user.Username);

  while (fgets(registerDb, sizeof(registerDb), database)) {
    char formatString[50];
    sprintf(formatString, "- %%d - %%%ds", lenghtUsername);

    char username[48] = "";
    int usernameID = 0;
    sscanf(registerDb, formatString, &usernameID, &username); 

    if (lineWithData > 3 && (lineWithData % 2) == 0) {
      if (strcmp(user.Username, username)) {
        strcat(tempDataBase, registerDb);
        stopPrint++;
      } else {
        strcat(tempDataBase, "-          -                                                  -                                                  -\n");
        strcat(tempDataBase, "------------------------------------------------------------------------------------------------------------------\n");
        stopPrint = 0;
        if (defaul) {
          user = findUserByRoot(&user, result);
          removeGraphic(&user, 0, defaul);
        }
      }
    };

    if (lineWithData == 2) {
      strcat(tempDataBase, "- ID       - Username                                         - Password                                         -\n");
    }

    if ((lineWithData % 2) == 1 && stopPrint){
      strcat(tempDataBase, "------------------------------------------------------------------------------------------------------------------\n");
    }
    lineWithData++;
  };
  fclose(database);

  FILE* newDataBase = fopen("database.txt", "w");

  if (!newDataBase) {
    printf("Error al abrir los archivos.\n");
    return 0;
  }

  fprintf(newDataBase, tempDataBase);

  fclose(newDataBase);

  return result;
}


/** Compara dos fechas en formato "dd-mm-aa".
  * @param date1: Primera fecha a comparar.
  * @param date2: Segunda fecha a comparar.
  * @return: Devuelve -1 si date1 es menor que date2, 1 si date1 es mayor que date2, y 0 si son iguales.
  */
int compareDates(const char *date1, const char *date2) {
  int day1, month1, year1;
  int day2, month2, year2;
  sscanf(date1, "%d-%d-%d", &day1, &month1, &year1);
  sscanf(date2, "%d-%d-%d", &day2, &month2, &year2);

  if (year1 < year2)
    return -1;
  else if (year1 > year2)
    return 1;
  else {
    if (month1 < month2)
      return -1;
    else if (month1 > month2)
      return 1;
    else {
      if (day1 < day2)
        return -1;
      else if (day1 > day2)
        return 1;
      else
        return 0;
    }
  }
}


/** Compara dos fechas en formato "dd-mm-aa" y ordena un arreglo de estructuras 'Graphics' por el valor de las fechas en orden ascendente.
  * @param arr El arreglo de estructuras 'Graphics' a ordenar.
  * @param size El tamaño del arreglo.
  */
void sortByDate(Graphics arr[], int size) {
  int i, j;
  for (i = 0; i < size - 1; i++) {
    for (j = 0; j < size - i - 1; j++) {
      if (compareDates(arr[j].date, arr[j + 1].date) > 0) {
        swapDate(&arr[j], &arr[j + 1]);
      }
    }
  }
}


/** Compara dos fechas en formato "dd-mm-aa" y ordena un arreglo de estructuras 'Graphics' por el valor de las fechas en orden descendente.
  * @param arr El arreglo de estructuras 'Graphics' a ordenar.
  * @param size El tamaño del arreglo.
  */
void sortByDateDescending(Graphics arr[], int size) {
  int i, j;
  for (i = 0; i < size - 1; i++) {
    for (j = 0; j < size - i - 1; j++) {
      if (compareDates(arr[j].date, arr[j + 1].date) < 0) {
        swapDate(&arr[j], &arr[j + 1]);
      }
    }
  }
}


/** Intercambia los valores de dos variables enteras.
  * @param a: Puntero al primer entero.
  * @param b: Puntero al segundo entero.
  */
void swapDate(Graphics* a, Graphics* b) {
    char temp[9];
    strcpy(temp, a->date);
    strcpy(a->date, b->date);
    strcpy(b->date, temp);
}


/** Se encarga de crear la base de datos que almacena las graficas de todos los usuarios:
  * @return devuelve un cero al finalizar su ejecucion.
  */
int createDbGraphics() {
  FILE* graphicsDb = fopen("dbgraphics.txt", "w");

  if (!graphicsDb) {
    printf("Error al crear la base de datos.\n");
    return 0;
  }

  fprintf(graphicsDb, "----------------------------------------------------------------------------------------------------------------------------------\n");
  fprintf(graphicsDb, "- UsernameID  - Date       - Graphic                        - Rangom             - RangoM             - Incremt            - ID  -\n");
  fprintf(graphicsDb, "----------------------------------------------------------------------------------------------------------------------------------\n");

  fclose(graphicsDb);
  return 0;
};


/** Se encarga de crear un nuevo registro con una grafica polinomica nueva que se generara con el
  * ID del usuario para que esta pertenezca a el:
  * @param user contiene la informacion del usuario actual.
  * @param result parametro extra obligatorios para poder llarmar la funcion.
  * @param defaul parametro extra obligatorios para poder llarmar la funcion.
  * @return devuelve un cero al finalizar su ejecucion.
  */
int createNewGraphic( Users* user, int result, int defaul ) {
  FILE* graphicsDb = fopen("dbgraphics.txt", "a");

  if (!graphicsDb) {
    printf("Error al crear la base de datos.\n");
    return 0;
  }

  Graphics graphic;

  graphic.UsernameID = user->ID;

  fflush(stdin);
  printf("Ingrese la funcion polinomica: ");
  scanf("%s", &graphic.function);
  printf("Ingrese el rango menor: ");
  scanf("%i", &graphic.rangem);
  printf("Ingrese el rango mayor: ");
  scanf("%i", &graphic.rangeM);
  printf("Ingrese el incremento: ");
  scanf("%i", &graphic.incremt);

  int lengthGraphic = strlen(graphic.function);
  char spaceGraphic[29] = "";

  while (lengthGraphic < 30) {
    strcat(spaceGraphic, " ");
    lengthGraphic++;
  }
  
  char spacesRangeM[20] = "";
  char spacesRangem[20] = "";
  char spacesIncrmt[20] = "";

  int rangem = graphic.rangem;
  int stoper = 1;
  while (abs(rangem) <= 999999) {
    if (rangem > 0 && stoper) {
      strcat(spacesRangem, " ");
      stoper = 0;
    }
    strcat(spacesRangem, " ");
    rangem *= 10;
  }

  int rangeM = graphic.rangeM;
  stoper = 1;
  while (abs(rangeM) <= 999999) {
    if (rangeM > 0 && stoper) {
      strcat(spacesRangeM, " ");
      stoper = 0;
    }
    strcat(spacesRangeM, " ");
    rangeM *= 10;
  }

  int incremt = graphic.incremt;
  while (incremt <= 999999) {
    strcat(spacesIncrmt, " ");
    incremt *= 10;
  }

  time_t t = time(NULL);
  struct tm *now = localtime(&t);

  int year = (now->tm_year + 1900) % 100;
  int month = now->tm_mon + 1;
  int day = now->tm_mday; 

  char fecha[9];
  sprintf(fecha, "%i-%i-%i", year, month, day);

  int referenceID = assignUniqueReference(0);
  char spaceReferenceID[5] = "";

  if (referenceID < 10){
    strcat(spaceReferenceID, " ");
  }

  if (user->ID < 10) {
    fprintf(graphicsDb, "- %i           - %s    - %s%s - %i%s           - %i%s           - %i%s            - %i%s  -\n", user->ID, fecha, graphic.function, spaceGraphic, graphic.rangem, spacesRangem, graphic.rangeM, spacesRangeM, graphic.incremt, spacesIncrmt, referenceID, spaceReferenceID);
    fprintf(graphicsDb, "----------------------------------------------------------------------------------------------------------------------------------\n");
  }
  
  if (user->ID >= 10){
    fprintf(graphicsDb, "- %i          - %s    - %s%s - %i%s            - %i%s            - %i%s            - %i%s   -\n", user->ID, fecha, graphic.function, spaceGraphic, graphic.rangem, spacesRangem, graphic.rangeM, spacesRangeM, graphic.incremt, spacesIncrmt, referenceID, spaceReferenceID);
    fprintf(graphicsDb, "----------------------------------------------------------------------------------------------------------------------------------\n");
  }
  

  fclose(graphicsDb);
  system("cls");
  return 0;
};


/** Se encarga de crear un nuevo registro con una grafica polinomica nueva que se generara con el
  * ID del usuario para que esta pertenezca a el:
  * @param user contiene la informacion del usuario actual.
  * @param result almacenara el resultado de la busqueda, o sea el estado.
  * @param defaul almacena la razon por la cual se esta ejecutando la busqueda si es un 0,
  * es porque se busca mostrar la grafica, si es un 1 es porque solo se desea mostrar la informacion.
  * @return devuelve un result al terminar la ejecucion.
  */
int findOneGraphic( Users* user, int result, int defaul ) {
  FILE* graphicsDb = fopen("dbgraphics.txt", "r");
  Users userGraphic;
  Graphics graphic;
  int graphicId;

  if (!graphicsDb) {
    printf("Error al abrir el archivo de la base de datos.\n");
    return 0;
  }

  printf("Aplicativo - graficador - UTP - impresion de grafica por referencia\n");
  printf("Entre Nrp {referencia}:");
  fflush(stdin);
  scanf("%i", &graphicId);

  char registerdb[132] = "";
  int lineWithData = 1;

  while (fgets(registerdb, sizeof(registerdb), graphicsDb)) {
    sscanf(registerdb, "- %i - %8s - %30s - %i - %i - %i - %i", &graphic.UsernameID, graphic.date, graphic.function, &graphic.rangem, &graphic.rangeM, &graphic.incremt, &graphic.ID);

    if (lineWithData > 3 && (lineWithData % 2) == 0) {
      if ((graphicId == graphic.ID)) {
        if (defaul == 2) {
          userGraphic.ID = graphic.UsernameID;
          userGraphic = findUserByRoot(&userGraphic, result);
          printf("Username: %s Fecha: %s\n", userGraphic.Username, graphic.date);
          printf("f(x) = %s Rango: %i a %i. Incremento: %i\n", graphic.function, graphic.rangem, graphic.rangeM, graphic.incremt);
          viewGraphicFunction(&graphic);
          return result;
        }
        if (defaul == 0 && graphic.UsernameID == user->ID) {
          userGraphic = *user;
          printf("Username: %s Fecha: %s\n", userGraphic.Username, graphic.date);
          printf("f(x) = %s Rango: %i a %i. Incremento: %i\n", graphic.function, graphic.rangem, graphic.rangeM, graphic.incremt);
          viewGraphicFunction(&graphic);
          return result;
        }
      }
    }
    lineWithData++;
  }
  fclose(graphicsDb);

  printf("El grafico pedido no existe\n");
  sleep(2);
  return result;
};


/** Se encarga de crear un nuevo registro con una grafica polinomica nueva que se generara con el
  * ID del usuario para que esta pertenezca a el:
  * @param user contiene la informacion del usuario actual.
  * @param result almacenara el resultado de la busqueda, o sea el estado.
  * @param defaul almacena la razon por la cual se esta ejecutando la busqueda si es un 0,
  * es porque se busca mostrar la grafica, si es un 1 es porque solo se desea mostrar la informacion.
  * @return devuelve un result al terminar la ejecucion.
  */
int findAllGraphics(Users* user, int result, int defaul) {
  FILE* graphicsDb = fopen("dbgraphics.txt", "r");

  if (!graphicsDb) {
    printf("Error al abrir el archivo de la base de datos.\n");
    return 0;
  }

  Graphics graphics[50];
  int numGraphics = 0;

  char registerdb[132] = "";
  int stopFind = 1;
  int lineWithData = 1;

  while (fgets(registerdb, sizeof(registerdb), graphicsDb) && stopFind) {
    Graphics graphic;
    sscanf(registerdb, "- %i - %8s - %30s - %i - %i - %i - %i", &graphic.UsernameID, graphic.date, graphic.function, &graphic.rangem, &graphic.rangeM, &graphic.incremt, &graphic.ID);

    int registerVoid = registerdb[2] == ' ';

    if (lineWithData > 3 && (lineWithData % 2) == 0 && !registerVoid) {
      if (graphic.UsernameID == user->ID) {
        graphics[numGraphics] = graphic;
        numGraphics++;
      }
    }
    lineWithData++;
  }

  fclose(graphicsDb);

  if (defaul == 1) {
    sortByDate(graphics, numGraphics);
  } else if (defaul == 2) {
    sortByDateDescending(graphics, numGraphics);
  }
  

  printAccess(user, graphics, defaul, numGraphics);

  return result;
};


/** Se encarga de mostrar todos los accesos del usuario seleccionado:
  * @param user contiene la informacion del usuario actual.
  * @param result parametro extra obligatorios para poder llarmar la funcion.
  * @param defaul parametro extra obligatorios para poder llarmar la funcion.
  * @return devuelve un estado result al finalizar su ejecucion.
  */
int viewAccessUser( Users* user, int result, int defaul ) {
  int ordenSite = 1;

  if (result == 1) {
    printf("Aplicativo - graficador - UTP\n");
    printf("Acesos del usuario %s\n", user->Username);
    printf("Ordenar por fecha. Presione(1) Orden ascendente (2) Orden Descendente: ");
    scanf("%i", &ordenSite);
    findAllGraphics(user, result, ordenSite);
  }
  
  if (result == 2) {
    Users userFind;
    printf("Aplicativo - graficador - UTP\n");
    printf("Listado de accesos por usuario\n");
    printf("Username: ");
    fflush(stdin);
    fgets(userFind.Username, 48, stdin);
    userFind.Username[strlen(userFind.Username) - 1] = '\0';
    userFind = findUserByRoot(&userFind, result);
    if (userFind.ID == 0){
      return 0;
    }
    printf("Ordenar por fecha. Presione(1) Orden ascendente (2) Orden Descendente: ");
    scanf("%i", &ordenSite);
    findAllGraphics(&userFind, result, ordenSite);
  }

  system("pause");
  system("cls");
  return result;
};


/** Se encarga de controlar el orden en la vista de accesos para todos
  * los usuario: 
  * @param user contiene la informacion del usuario actual.
  * @param result parametro extra obligatorios para poder llarmar la funcion.
  * @param defaul parametro extra obligatorios para poder llarmar la funcion.
  * @return devuelve un estado result al finalizar su ejecucion.
  */
int viewAccessUsers( Users* user, int result, int defaul ) {
  int ordenSite = 1;

  if (result == 1) {
    printf("Aplicativo - graficador - UTP\n");
    printf("Acesos del usuario %s\n", user->Username);
    printf("Ordenar por fecha. Presione(1) Orden ascendente (2) Orden Descendente: ");
    scanf("%i", &ordenSite);
    findAllUsersByRoot(user, result, ordenSite);
  }

  system("pause");
  system("cls");
  return result;
};


/** Se encarga de mostrar en pantalla todos los accesos de un usuario en el orden que
  * le alla llegado como parametro en order:
  * @param user almacena la informacion del dueño de la grafica.
  * @param graphic almacena la informacion de las graficas del usuario almacenado en user.
  * @param order almacena el valor del orden en el que se desea ver los accesos.
  * @param numGraphics almacena el total de graficas que contiene el usuario
  * @return retorna un cero despues de filazar su ejecucion.
  */
int printAccess( Users* user, Graphics* graphic, int order, int numGraphics ) {
  if (order == 1) {
    printf("Listado de accesos ordenado ascendente (0--%d) por fecha\n", numGraphics - 1);
  } else {
    printf("Listado de accesos ordenado descendente (%d--0) por fecha\n", numGraphics - 1);
  }
  
  printf("Fecha      Nro grafico   Polinomio-F(x)\n");
  
  if (order == 1) {
    for (int i = 0; i < numGraphics; i++) {
      int quitPipe = strlen(graphic[i].date);
      graphic[i].date[quitPipe - 1] = '\0';
      printf("20%s         %i         %s\n", graphic[i].date, graphic[i].ID, graphic[i].function);
    }
  } else {
    for (int i = 0; i < numGraphics; i++) {
      int quitPipe = strlen(graphic[i].date);
      graphic[i].date[quitPipe - 1] = '\0';
      printf("20%s         %i         %s\n", graphic[i].date, graphic[i].ID, graphic[i].function);
    }
  }
  
  printf("------------------------------------------------------------\n");
  printf("%d Registros\n", numGraphics);
  return 0;
}


/** Se encarga de eliminar el registro de una grafica para el usuario que se encuentre
  * usando el programa, solo si el grafico es suyo:
  * @param user contiene la informacion del usuario actual.
  * @param result parametro extra obligatorios para poder llarmar la funcion.
  * @param defaul parametro extra obligatorios para poder llarmar la funcion.
  * @return devuelve un estado result al finalizar su ejecucion.
  */
int removeGraphic( Users* user, int result, int defaul ) {
  FILE* graphicsDb = fopen("dbgraphics.txt", "r");
  int graphicID = 0;

  if (!graphicsDb) {
    printf("Error al abrir el archivo de la base de datos.\n");
    return 0;
  }

  Graphics graphic;

  if (!defaul) {
    printf("Ingrese el numero de referencia de la grafica que desea eliminar: ");
    scanf("%i", &graphicID);
  }

  char registerDb[132] = "";
  char tempDataBase[10000] = "";
  int stopPrint = 1;
  int lineWithData = 1;

  if (!defaul) {
    while (fgets(registerDb, sizeof(registerDb), graphicsDb)) {
      sscanf(registerDb, "- %i - %8s - %30s - %i - %i - %i - %i", &graphic.UsernameID, graphic.date, graphic.function, &graphic.rangem, &graphic.rangeM, &graphic.incremt, &graphic.ID);

      if (lineWithData > 3 && (lineWithData % 2) == 0) {
        if (graphicID == graphic.ID && graphic.UsernameID == user->ID) {
          strcat(tempDataBase, "-             -            -                                -                    -                    -                    -     -\n");
          strcat(tempDataBase, "----------------------------------------------------------------------------------------------------------------------------------\n");
          if (!defaul) stopPrint = 0;
         } else {
          strcat(tempDataBase, registerDb);
          stopPrint++;
        }
      }
      if (lineWithData == 2) {
        strcat(tempDataBase, "- UsernameID  - Date       - Graphic                        - Rangom             - RangoM             - Incremt            - ID  -\n");
      }
      if ((lineWithData % 2) == 1 && stopPrint) {
        strcat(tempDataBase, "----------------------------------------------------------------------------------------------------------------------------------\n");
      }
      lineWithData++;
    }
  } else {
    while (fgets(registerDb, sizeof(registerDb), graphicsDb)) {
      sscanf(registerDb, "- %i - %8s - %30s - %i - %i - %i - %i", &graphic.UsernameID, graphic.date, graphic.function, &graphic.rangem, &graphic.rangeM, &graphic.incremt, &graphic.ID);

      if (lineWithData > 3 && (lineWithData % 2) == 0) {
        if (graphic.UsernameID == user->ID) {
          strcat(tempDataBase, "-             -            -                                -                    -                    -                    -     -\n");
          strcat(tempDataBase, "----------------------------------------------------------------------------------------------------------------------------------\n");
          stopPrint = 0;
        } else {
          strcat(tempDataBase, registerDb);
          stopPrint++;
        }
      }

      if (lineWithData == 2) {
        strcat(tempDataBase, "- UsernameID  - Date       - Graphic                        - Rangom             - RangoM             - Incremt            - ID  -\n");
      }

      if ((lineWithData % 2) == 1 && stopPrint) {
        strcat(tempDataBase, "----------------------------------------------------------------------------------------------------------------------------------\n");
      }
      lineWithData++;
    }
  }
  
  fclose(graphicsDb);

  FILE* newGraphicsDb = fopen("dbgraphics.txt", "w");

  if (!newGraphicsDb) {
    printf("Error al abrir el archivo de la base de datos.\n");
    return 0;
  }

  fprintf(newGraphicsDb, tempDataBase);

  fclose(newGraphicsDb);

  return result;
}


/** Se encarga de separar una funcion polinomica guardada como un string en
  * strings separados correspondientes a cada monomio de la funcion:
  * @param function almacena la funcion polinomica.
  * @param extractMon almacena el monomio extraido.
  * @param x contiene el valor de x que pertenece a cada intervalo
  * que se calculara en la funcion.
  * @return llamado a otra funcion para terminar la ejecucion del programa
  * o su propio llamado recursivo, para obtener el valor de toda la funcion polinomica.
  */
int separatedMonomios(char function[30], char extractMon[10], int x) {
  int i = 1; // contador para el polinomio
  int j = 0; // contador para desagregar el mononio extraido de la funcion
  int endMon = 0; // obtiene la posicion del final del monomio
  char tempFunction[30];
  strcpy(tempFunction, function);

  while (!endMon) {
    (tempFunction[i] == '+' || tempFunction[i] == '-' || tempFunction[i] == '\0') ? endMon = i : i++;
  }

  memcpy(extractMon, tempFunction, endMon);
  extractMon[endMon] = '\0';

  while (tempFunction[i] != '\0') {
    tempFunction[j] = tempFunction[i];
    j++; 
    i++;
  }

  tempFunction[j] = '\0';


  if (tempFunction[0] != '\0') {
    return (fxValues(extractMon, x) + separatedMonomios(tempFunction, extractMon, x));
  }
  return fxValues(extractMon, x);
};


/** Se encarga de generar los valores de f(x) a partir del intervalo ingresado o añadido:
  * @param extractedMon corresponde al monomio extraido de la funcion polinomica.
  * @param x corresponde al valor de x que se esta analizando.
  * @return se encarga de ir devolviendo el resultado de hacer la operacion de cada monomio
  */
int fxValues(char extractedMon[10], int x) {
  char coef[10] = "";
  int xPosition = strchr(extractedMon, 'x') - extractedMon;

  if (strchr(extractedMon, 'x') != NULL) {
    if (extractedMon[0] == 'x' || ((extractedMon[0] == '+') && (extractedMon[1] == 'x'))) {
      coef[0] = '1';
      coef[1] = '\0';
    } else if ((extractedMon[0] == '-') && (extractedMon[1] == 'x')) {
      coef[0] = '-';
      coef[1] = '1';
      coef[2] = '\0';
    } else {
      memcpy(coef, extractedMon, xPosition);
      coef[xPosition] = '\0';
    }

    if (extractedMon[xPosition + 1] == '\0') {
      extractedMon[xPosition + 1] = '1';
      extractedMon[xPosition + 2] = '\0';
    }
  } else {
    return atoi(extractedMon);
  }

  return atoi(coef) * pow(x, atoi(&extractedMon[xPosition + 1]));
}


/** Se encarga de eliminar el registro de una grafica para el usuario que se encuentre
  * usando el programa, solo si el grafico es suyo:
  * @param user contiene la informacion del usuario actual.
  * @param result parametro extra obligatorios para poder llarmar la funcion.
  * @param defaul parametro extra obligatorios para poder llarmar la funcion.
  * @return devuelve un estado result al finalizar su ejecucion.
  */
int initGraphicate( Users* user, int result, int defaul ) {
  findOneGraphic(user, result, defaul);
  return result;
}


/** Se encarga de extraer el total de puntos que hay que graficar y luego almacena 
  * los valores de x y de y en un arreglo para pasarlos a otra funcion que los ordenara:
  * @param graphic contiene toda la informacion perteneciente a la grafica
  * que debemos mostrar
  * @return 
  */
int viewGraphicFunction( Graphics* graphic) {
  int count = 0;
  int obtainPosition = 0;
  int iteration = graphic->rangem;
  while (iteration <= graphic->rangeM) {
    iteration+= graphic->incremt;
    count++;
  }

  char monomial[10];

  int xValues[count];
  int yValues[count];

  iteration = graphic->rangem;
  while (iteration <= graphic->rangeM) {
    xValues[obtainPosition] = iteration;
    yValues[obtainPosition] = separatedMonomios(graphic->function, monomial, iteration);
    iteration+= graphic->incremt;
    obtainPosition++;
  }

  controlValues(xValues, yValues, obtainPosition);
}


/** Se encarga de ordenar el arreglo de yValues de menor a mayor, luego de validar los
  * cuadrantes que se van a usar y llamar a una funcion que decide que tipo de plano
  * hay que armar:
  * @param xValues almacena el arreglo con la informacion de los valores de x.
  * @param yValues almacena el arreglo con la informacion de los valores de y.
  * @param size almacena el tamaño del arreglo de numero
  * @return no devuelve nada especial, solo se encarga del control de datos para
  * la grafica.
  */
int controlValues( int xValues[], int yValues[], int size ) {
  GraphicInformation InfoGraphic;
  int yValuesSort[size];
  for (int i = 0; i < size; i++) {
    yValuesSort[i] = yValues[i];
  }

  quicksort(yValuesSort, 0, size - 1);
  validateQuadrants(&InfoGraphic, xValues, yValuesSort, size);
  selectGraphicPosible(&InfoGraphic, xValues, yValues,yValuesSort, size);
}


/** Se encarga de ordenar el arreglo de yValues de menor a mayor, ....
  * @param xValues almacena el arreglo con la informacion de los valores de x.
  * @param yValues almacena el arreglo con la informacion de los valores de y.
  * @param size almacena el tamaño del arreglo de numero
  * @return no devuelve nada especial, solo se encarga de definir el tipo de plano que se debera crear
  */
int selectGraphicPosible( GraphicInformation* Info,  int xValues[], int yValues[], int yValuesOrdered[], int size ) {
  if (Info->itsUsed.quadrantsOne && Info->itsUsed.quadrantsThree || Info->itsUsed.quadrantsTwo && Info->itsUsed.quadrantsFourt) {
    obtainRatioAxis(Info, xValues, yValuesOrdered, size, 1);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  } else if (Info->itsUsed.quadrantsOne && Info->itsUsed.quadrantsTwo) {
    obtainRatioAxis(Info, xValues, yValuesOrdered, size, 2);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  } else if (Info->itsUsed.quadrantsThree && Info->itsUsed.quadrantsFourt) {
    obtainRatioAxis(Info, xValues, yValuesOrdered, size, 3);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  } else if (Info->itsUsed.quadrantsOne && Info->itsUsed.quadrantsFourt) {
    obtainRatioAxis(Info, xValues, yValuesOrdered, size, 1);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  } else if (Info->itsUsed.quadrantsThree && Info->itsUsed.quadrantsTwo) {
    obtainRatioAxis(Info, xValues, yValuesOrdered, size, 1);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  } else if (Info->itsUsed.quadrantsOne) {
    Info->center.xCenter = 16;
    Info->center.yCenter = 624;
    Info->intervalAxisX = 640 / (size - 1);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  } else if (Info->itsUsed.quadrantsTwo) {
    Info->center.xCenter = 624;
    Info->center.yCenter = 624;
    Info->intervalAxisX = 640 / (size - 1);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  } else if (Info->itsUsed.quadrantsThree) {
    Info->center.xCenter = 624;
    Info->center.yCenter = 16;
    Info->intervalAxisX = 640 / (size - 1);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  } else if (Info->itsUsed.quadrantsFourt) {
    Info->center.xCenter = 16;
    Info->center.yCenter = 16;
    Info->intervalAxisX = 640 / (size - 1);
    obtainCoordinates(Info, xValues, yValues, yValuesOrdered, size);
  }

  graphicater(Info, size);

  return 0;
};


/** Intercambia los valores de dos variables enteras.
  * @param a: Puntero al primer entero.
  * @param b: Puntero al segundo entero.
  */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


/** Realiza la partición del arreglo en torno a un pivote.
  * Coloca los elementos menores que el pivote a su izquierda y los elementos mayores a su derecha.
  * @param arr: Arreglo de enteros a ser particionado.
  * @param low: Índice inferior del subarreglo a ser particionado.
  * @param high: Índice superior del subarreglo a ser particionado.
  * @return: Índice del pivote después de la partición.
  */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


/** Implementa el algoritmo de Quicksort para ordenar un arreglo de enteros en orden ascendente.
  * @param arr: Arreglo de enteros a ser ordenado.
  * @param low: Índice inferior del subarreglo a ser ordenado.
  * @param high: Índice superior del subarreglo a ser ordenado.
  */
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}


/** Se encarga de analizar cuales de los cuadrantes del plano cartesiano necesitan
  * ser usados para graficar la funcion:
  * @param Info estructura de informacion grafica para almacenar la informacion en ella.
  * @param xValues arreglo de valores del eje x.
  * @param yValues arreglo de valores del eje y ordenados de menor a mayor.
  * @param size tamaño de los arreglos con las coordenadas sin escala en pixeles.
  * @return no devuelve nada, solo ingresa informacion en la estructura de informacion grafica.
 */
int validateQuadrants( GraphicInformation* Info,  int xValues[], int yValues[], int size ) {
  Info->itsUsed.quadrantsOne = 0;
  Info->itsUsed.quadrantsTwo = 0;
  Info->itsUsed.quadrantsThree = 0;
  Info->itsUsed.quadrantsFourt = 0;

  if (xValues[size - 1] >= 0 && yValues[size - 1] >= 0) {
    Info->itsUsed.quadrantsOne = 1;
  }
  if (xValues[0] < 0 && yValues[size - 1] >= 0) {
    Info->itsUsed.quadrantsTwo = 1;
  }
  if (xValues[0] < 0 && yValues[0] < 0) {
    Info->itsUsed.quadrantsThree = 1;
  }
  if (xValues[size - 1] >= 0 && yValues[0] < 0) {
    Info->itsUsed.quadrantsFourt = 1;
  }
};


/** Se encarga de analizar cualo debe ser la proporcion del los ejes para conocer cual va 
  * a ser el centrod el plano cartesiano:
  * @param Info estructura de informacion grafica para almacenar la informacion en ella.
  * @param xValues arreglo de valores del eje x.
  * @param yValues arreglo de valores del eje y ordenados de menor a mayor.
  * @param size tamaño de los arreglos con las coordenadas sin escala en pixeles.
  * @return no devuelve nada, solo ingresa informacion en la estructura de informacion grafica.
  */
int obtainRatioAxis( GraphicInformation* Info,  int xValues[], int yValues[], int size, int notSearch ) {
  Info->axisSize.yAxis[0] = 0;
  Info->axisSize.yAxis[1] = 0;

  if (notSearch == 1) {
    if (abs(yValues[0]) > (yValues[size - 1])) {
      float valueOne = abs(yValues[0]);
      float valueTwo = yValues[size - 1];
      float axisOne;
      if (abs(xValues[0]) == xValues[size - 1]) {
        axisOne = (valueTwo / valueOne * 1.0) / 2;
      } else {
        axisOne = valueTwo / valueOne * 1.0;
      }
      Info->axisSize.yAxis[0] = axisOne * 640;
    } else if (abs(yValues[0]) < yValues[size - 1]) {
      float valueOne = abs(yValues[0]);
      float valueTwo = yValues[size - 1];
      float axisOne;
      if (abs(xValues[0]) == xValues[size - 1]) {
        axisOne = 1 - ((valueOne / valueTwo * 1.0) / 2);
      } else {
        axisOne = 1 - (valueOne / valueTwo * 1.0);
      }
      Info->axisSize.yAxis[0] = axisOne * 640;
    } else {
      Info->axisSize.yAxis[0] = 320;
    }
  }
  Info->intervalAxisX = 640 / (size - 1);
  Info->axisSize.yAxis[1] = 640 - Info->axisSize.yAxis[0];
  obtainZeroZero(Info, xValues, yValues, size, notSearch);
}


/** Se encarga de obtener las coordenadas donde se encuentra la intersecion entre los ejes del plano:
  * @param Info estructura de informacion grafica para almacenar la informacion en ella.
  * @param xValues arreglo de valores del eje x.
  * @param yValues arreglo de valores del eje y ordenados de menor a mayor.
  * @param size tamaño de los arreglos con las coordenadas sin escala en pixeles.
  * @return no devuelve nada, solo ingresa informacion en la estructura de informacion grafica.
  */
int obtainZeroZero( GraphicInformation* Info,  int xValues[], int yValues[], int size, int cuadrant ) {
  Info->center.xCenter = 0;
  Info->center.yCenter = 0;

  if (cuadrant == 2) {
    Info->center.yCenter = 624;
  } else if (cuadrant == 3) {
    Info->center.yCenter = 16;
  } else {
    Info->center.yCenter = Info->axisSize.yAxis[0];
  }

  int distansUntilZero = 0;
  int existZero = 0;
  int posZero = 0;
  for (int i = 0; i < size; i++) {
    if (xValues[i] <= 0) {
      existZero = 1;
      posZero = i;
    }
    distansUntilZero++;
  }

  if (existZero) {
    Info->center.xCenter = Info->intervalAxisX * posZero;
    return 0;
  }
};


/** Se encarga de generar pares de coordenadas en escala e ingresarlas en una estructura:
  * @param Info estructura de informacion grafica para almacenar la informacion en ella.
  * @param xValues arreglo de valores del eje x.
  * @param yValues arreglo de valores del eje y ordenados de menor a mayor.
  * @param size tamaño de los arreglos con las coordenadas sin escala en pixeles.
  * @return no devuelve nada, solo ingresa informacion en la estructura de informacion grafica.
  */
int obtainCoordinates( GraphicInformation* Info,  int xValues[], int yValues[], int yValuesOrdered[], int size ) {  
  for (int i = 0; i < size; i++) {
    if (yValues[i] >= 0) {
      int axisY = Info->center.yCenter * yValues[i] / yValuesOrdered[size - 1];
      Info->point[i].x = Info->intervalAxisX * i;
      Info->point[i].y = abs((-1 * axisY) + Info->center.yCenter);
      Info->coord[i].valueX = xValues[i];
      Info->coord[i].valueY = yValues[i];
    }
    if (yValues[i] < 0) {
      int axisY = (640 - Info->center.yCenter) * yValues[i] / yValuesOrdered[0];
      Info->point[i].x = Info->intervalAxisX * i;
      Info->point[i].y = abs((1 * axisY) + Info->center.yCenter);
      Info->coord[i].valueX = xValues[i];
      Info->coord[i].valueY = yValues[i];
    }
    Info->point[i].x = Info->intervalAxisX * i;
    Info->coord[i].valueX = xValues[i];
    Info->coord[i].valueY = yValues[i];
  }
};


/** Se encarga liberar la memoria y destruir los objetos generados por sdl2 antes de acabar el programa:
 * @param info estructura para almacenar la informacion necesaria para crear una grafica
 * @return 1 si hubo un error al generarse la grafica y 0 si se generó correctamente
 */
int graphicater(GraphicInformation *info, int size) {
  imprimirDatos(info, size);
  // Inicializamos SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initializing SDL2: %s\n", SDL_GetError());
    return 1;
  }

  // Inicializamos TTF
  TTF_Init();

  // Declaramos una tipado de fuente que rellenaremos luego
  TTF_Font *font = NULL;

  // Declaramos una variable para poder manejar eventos (en este caso cerrar la ventana)
  SDL_Event event;

  // Creamos una ventana
  SDL_Window *window = SDL_CreateWindow("Plano Cartesiano", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_SHOWN);

  // Verificamos si la ventana logró crearse de manera exitosa, sino imprime el error y retorna 1
  if (window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Declaramos el renderizados que usaremos para poder dibujar graficos en la ventana
  SDL_Renderer *plano = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // Verificamos si el render logró crearse de manera exitosa, sino imprime el error y retorna 1
  if (plano == NULL) {
    printf("Error creating \"plano\": %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Color blanco al fondo del plano
  SDL_SetRenderDrawColor(plano, 234, 250, 241, 255);

  // Limpiamos la ventana
  SDL_RenderClear(plano);

  // Color negro a las lineas a dibujar

  drawFuction(plano, font, info->center, info->point, size, info->coord, info->totalIntervalX);
  SDL_RenderPresent(plano);

  int close = 0;
  while (!close) {
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
      close = 1;
    }
  }

  system("cls");
  SDL_DestroyRenderer(plano);
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_CloseFont(font);
  TTF_Quit();
  return 0;
}


/** Función encargada de dibujar los cuadrantes, sus divisiones y la grafica:
 * @param plano, puntero al renderer sobre el cuál queremos renderizar
 * @param center, estructura que contendrá los valores del (0,0) en escala con respecto al plano
 * @param point, Estructura de vectores que contiene el valor de X y Y de la función
 * @param size, el tamaño del todos los vectores destinados a graficar
 * @return no devuelve nada
 */
void drawFuction(SDL_Renderer *plano, TTF_Font *font, CenterGraphic center, Point point[], int size, CoordPlanes coor[], int incrementX) {

  SDL_SetRenderDrawColor(plano, 20, 90, 50, 255);
  // Graficamos el eje Y
  if (!((coor[0].valueX > 0 && coor[size - 1].valueX > 0) || (coor[0].valueX < 0 && coor[size - 1].valueX < 0))) {
    SDL_RenderDrawLine(plano, center.xCenter, 0, center.xCenter, 640);
  }

  // Graficamos el eje X
  SDL_RenderDrawLine(plano, 0, center.yCenter, 640, center.yCenter);

  // Hacemos iteraciones para realizar las divisiones entre los ejes
  for (int i = 0; i <= size; i++) {
    if (size - 1 == i){
      // Vamos a graficar las divisones del eje X
      SDL_SetRenderDrawColor(plano, 20, 90, 50, 255);
      SDL_RenderDrawLine(plano, point[i].x - 10, center.yCenter - 5, point[i].x - 10, center.yCenter + 5);
      numbers(plano, font, point[i].x - 10, center.yCenter - 20, coor[i].valueX);
      // Vamos a graficar las divisones del eje Y
      SDL_SetRenderDrawColor(plano, 20, 90, 50, 255);
      SDL_RenderDrawLine(plano, center.xCenter - 5, point[i].y - 10, center.xCenter + 5, point[i].y - 10);
      numbers(plano, font, center.xCenter, point[i].y - 10, coor[i].valueY);
    } else {
      // Vamos a graficar las divisones del eje X
      SDL_SetRenderDrawColor(plano, 20, 90, 50, 255);
      SDL_RenderDrawLine(plano, point[i].x, center.yCenter - 5, point[i].x, center.yCenter + 5);
      numbers(plano, font, point[i].x, center.yCenter - 20, coor[i].valueX);
      // Vamos a graficar las divisones del eje Y
      SDL_SetRenderDrawColor(plano, 20, 90, 50, 255);
      SDL_RenderDrawLine(plano, center.xCenter - 5, point[i].y, center.xCenter + 5, point[i].y);
      numbers(plano, font, center.xCenter, point[i].y, coor[i].valueY);
    }
  }


  // Dibujamos la grafica
  SDL_Point sdlPoints[size];
  for (int i = 0; i < size; i++) {
    sdlPoints[i].x = point[i].x;
    sdlPoints[i].y = point[i].y;
  }
  SDL_SetRenderDrawColor(plano, 100, 30, 22, 255);
  SDL_RenderDrawLines(plano, sdlPoints, size);
}

/** Función encargada de renderizar el valor de las divisiones:
 * @param render puntero del renderer a destruir.
 * @param font puntero de la fuente q usaremos
 * @param x coordenada en X (px) donde pondremos el numero
 * @param y coordenada en Y (px) donde pondremos el numero
 * @param num numero el cuál pegaremos en las coordenadas (x,y)
 * @return no devuelve nada
 */
void numbers(SDL_Renderer *render, TTF_Font *font, int x, int y, int num) {
  
  // Cargar una fuente
  font = TTF_OpenFont(Fuente, letterSize);
  if (!font) {
    printf("Error al cargar la fuente: %s\n", TTF_GetError());
  }

  // Variable que contendrá las cifras del numero
  int contador = 1;

  // Variable que contendrá el valor de num para poder para la iteración y no edite el valor original
  int numero = num;

  // Ciclo para saber cuantos digitos tiene un numero
  while (numero != 0) {
    numero = numero / 10;
    contador++;
  }

  // String donde guardaremos el numero que haremos string y a su vez imprimiremos
  char text[contador];

  sprintf(text, "%d", num);

  // Si num llegase a ser 0, haremos que imprima nada para que no estorbe a la vista
  if (num == 0) {
    text[0] = ' ';
    text[1] = '\0';
  }

  // Declaramos una superficie y una textura que pegaremos en el renderer luego de genererar el numero
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, (SDL_Color){0, 0, 0, 255});
  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(render, textSurface);

  SDL_Rect destRect;
  destRect.x = x;
  destRect.y = y;
  destRect.w = textSurface->w;
  destRect.h = textSurface->h;

  SDL_RenderCopy(render, textTexture, NULL, &destRect);

  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
}


/** Se enecarga de mostrar por consola el menu del usuario root:
  * @param root informacion del usuario root para mostrar su nombre en el menu.
  * @return no devuelve nada, solo se encarga de mostrar por consola el menu.
  */
int menuRootUser( Users* root ) {
  printf("Aplicativo - Graficador - UTP\n");
  printf("Menu principal para usuario: %s\n", root->Username);
  printf("0. Salir del aplicativo\n");
  printf("1. Crear nuevo usuario\n");
  printf("2. Borrar usuario\n");
  printf("3. Listar accesos por usuario\n");
  printf("4. Listar accesos todos los usuarios\n");
  printf("5. Imprimir grafico por referencia\n");
  printf("6. Cambiar password del usuario root\n");
  printf("7. Cambiar password de un usuario\n");
};


/** Se encarga de mostrar por consola el menu del usuario basico:
  * @param user informacion del usuario que ha iniciado sesion para mostrarla
  * en el menu.
  * @return no devuelve nada, solo se encarga de mostrar por consola el menu.
  */
int menuNormalUser( Users* user ) {
  printf("Aplicativo - Graficador - UTP\n");
  printf("Menu principal para usuario: %s\n", user->Username);
  printf("0. Salir del aplicativo\n");
  printf("1. Crear un nuevo grafico\n");
  printf("2. Borrar un grafico existente\n");
  printf("3. Listar accesos\n");
  printf("4. Imprimir grafico por referencia\n");
  printf("5. Cambiar password del usuario %s\n", user->Username);
}


/** Se encarga de ejecutar la opcion que el usuario root haya querido iniciar:
  * @param root contiene la informacion del usuario root.
  * @param option almacena la opcion que el usuario root haya elegido.
  * @return devuelve un 1 si la funcion se ejecuto correctamente, devuelve un 0
  * si no se pudo completar algun proceso.
  */
int handleRootUserOption ( Users* root, int option ) {
  MenuOption MenuOptions[] = {
    { createNewUser, root,  1, 0 },
    { removeUser, root, 1, 1 },
    { viewAccessUser, root, 2, 0},
    { viewAccessUsers, root, 1, 0},
    { initGraphicate, root, 1, 2},
    { changePassword, root, 1, 0},
    { changePasswordSelectAdmin, root, 1, 0}
  };
  
  system("cls");
  MenuOption Selected = MenuOptions[option - 1];
  Selected.function(Selected.nameUser, Selected.result, Selected.defaul);
  return 0;
};


/** Se enecarga de ejecutar la opcion que el usuario normal haya querido iniciar:
  * @param root contiene la informacion del usuario normal.
  * @param option almacena la opcion que el usuario normal haya elegido.
  * @return devuelve un 1 si la funcion se ejecuto correctamente, devuelve un 0
  * si no se pudo completar algun proceso.
  */
int handleNormalUserOption ( Users* user, int option ) {
  MenuOption MenuOptions[] = {
    { createNewGraphic, user,  1, 0},
    { removeGraphic, user, 1, 0 },
    { viewAccessUser, user, 1, 0},
    { initGraphicate, user, 1, 0},
    { changePassword, user, 1, 0}
  };
  
  system("cls");
  MenuOption Selected = MenuOptions[option - 1];
  Selected.function(Selected.nameUser, Selected.result, Selected.defaul);
  system("cls");
  return 0;
};