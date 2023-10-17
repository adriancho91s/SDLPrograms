#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define GAME_WIDTH 600
#define GAME_HEIGHT 600
#define CARD_WIDTH 300
#define CARD_HEIGHT 300
#define GRID_SIZE 2

static SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *surface = IMG_Load(path);
    if (!surface)
    {
        fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Memorama Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *cardTextures[GRID_SIZE * GRID_SIZE];
    const char *cardPaths[] = {
        "python.jpg", "javascript.jpg",
        "python.jpg", "javascript.jpg"};

    for (int i = 0; i < GRID_SIZE * GRID_SIZE; ++i)
    {
        cardTextures[i] = loadImage(renderer, cardPaths[i]);
        if (!cardTextures[i])
        {
            for (int j = 0; j < i; ++j)
            {
                SDL_DestroyTexture(cardTextures[j]);
            }
            IMG_Quit();
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }
    }

    srand(time(NULL));

    for (int i = GRID_SIZE * GRID_SIZE - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        SDL_Texture *temp = cardTextures[i];
        cardTextures[i] = cardTextures[j];
        cardTextures[j] = temp;
    }

    int revealed[GRID_SIZE * GRID_SIZE] = {0};
    int selected[2] = {-1, -1};
    int pairsFound = 0;

    SDL_Event event;
    int quit = 0;
    Uint32 startTicks = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x - (WINDOW_WIDTH - GAME_WIDTH) / 2;
                int y = event.button.y - (WINDOW_HEIGHT - GAME_HEIGHT) / 2;
                int col = x / CARD_WIDTH;
                int row = y / CARD_HEIGHT;
                int index = row * GRID_SIZE + col;

                if (x >= 0 && y >= 0 && x < GAME_WIDTH && y < GAME_HEIGHT && revealed[index] == 0 && selected[0] == -1)
                {
                    revealed[index] = 1;
                    selected[0] = index;
                }
                else if (x >= 0 && y >= 0 && x < GAME_WIDTH && y < GAME_HEIGHT && revealed[index] == 0 && selected[1] == -1)
                {
                    revealed[index] = 1;
                    selected[1] = index;

                    if (strcmp(cardPaths[selected[0]], cardPaths[selected[1]]) == 0)
                    {
                        revealed[selected[0]] = 2;
                        revealed[selected[1]] = 2;
                        pairsFound++;

                        // Check if all pairs have been found
                        if (pairsFound == GRID_SIZE * GRID_SIZE / 2)
                        {
                            printf("¡Felicidades, has ganado!\n");
                            quit = 1;
                        }

                        if (pairsFound <= 2)
                        { // Reset the selected cards
                            selected[0] = -1;
                            selected[1] = -1;
                        }
                    }
                    else
                    {
                        startTicks = SDL_GetTicks();
                    }
                }
            }
        }

        if (startTicks > 0 && SDL_GetTicks() - startTicks >= 2000)
        {
            if (pairsFound <= 2)
            {
                revealed[selected[0]] = 0;
                revealed[selected[1]] = 0;
                selected[0] = -1;
                selected[1] = -1;
            }
            startTicks = 0;
        }

        SDL_RenderClear(renderer);
        for (int i = 0; i < GRID_SIZE * GRID_SIZE; ++i)
        {
            int col = i % GRID_SIZE;
            int row = i / GRID_SIZE;
            SDL_Rect destRect = {(WINDOW_WIDTH - GAME_WIDTH) / 2 + col * CARD_WIDTH, (WINDOW_HEIGHT - GAME_HEIGHT) / 2 + row * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT};

            // Only render cards that are revealed or matched
            if (revealed[i] > 0)
            {
                SDL_RenderCopy(renderer, cardTextures[i], NULL, &destRect);
            }
        }
        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < GRID_SIZE * GRID_SIZE; ++i)
    {
        SDL_DestroyTexture(cardTextures[i]);
    }
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}