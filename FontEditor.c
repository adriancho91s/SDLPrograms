#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *args[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL\n");
        return -1;
    }
    SDL_Window *window = SDL_CreateWindow("Font editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 8 * 32,
                                          8 * 32, SDL_WINDOW_SHOWN);

    int pixels[8][8] = {};

    if (window == NULL) {
        printf("Error creating window\n");
    }

    int closed = 0;
    int buttonPressed = 0;

    while (!closed) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                closed = 1;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT)
                    buttonPressed = 1;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    buttonPressed = 2;
            }

            if (event.type == SDL_MOUSEBUTTONUP)
                buttonPressed = 0;

            if (buttonPressed != 0) {
                int posX = event.motion.x;
                int posY = event.motion.y;
                if (posX < 32 * 8 && posY < 32 * 8) {
                    int cellX = posX / 32;
                    int cellY = posY / 32;

                    if (buttonPressed == 1) {
                        pixels[cellY][cellX] = 1;
                    } else {
                        pixels[cellY][cellX] = 0;
                    }
                }
            }
        }

        SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {

                SDL_Rect rect;
                rect.x = x * 32;
                rect.y = y * 32;
                rect.h = 32;
                rect.w = 32;

                if (pixels[y][x] == 0) {
                    
                    SDL_FillRect(screenSurface, &rect, 0x00FFFFFF);
                } else {
                    SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 255, 0, 0));
                }
            }
        }

        SDL_UpdateWindowSurface(window);
        SDL_Delay(1);
    }
    FILE *of = fopen("output.txt", "w");

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            fprintf(of, "%d,", pixels[y][x]);
        }
    }

    fclose(of);
    SDL_Delay(100);
    system("nano ./output.txt");

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}