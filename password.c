#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#define BACKSPACE 127
#define ENTER 10
#define TAB 9

int main() {
    char password[100];
    int i = 0;
    char character;
    int exit = 0;

    printf("Enter your password. Hit ENTER to finish\n\n");
    printf("Password: ");

    while (exit != 1) {
        struct termios oldTerm, newTerm;
        tcgetattr(STDIN_FILENO, &oldTerm);
        newTerm = oldTerm;
        newTerm.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);

        character = getchar(); //Get Key

        tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
        // IF is necessary character == '\n' || character == '\r' || character == '\t'
        if (character == ENTER || character == TAB) {
            password[i] = '\0';
            exit = 1;
        } else if (character == BACKSPACE) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = character;
            printf("*");
        }
    }    

    printf("\nPassword entered: %s\n", password);

    return 0;
}