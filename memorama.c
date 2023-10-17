#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h> // Necesario para cargar imágenes


// Function for loading music to Mix_Music
static Mix_Music *loadMusic(const char *path)
{
    Mix_Music *music = Mix_LoadMUS(path);
    if (music == NULL)
    {
        fprintf(stderr, "Mix_LoadMUS Error: %s\n", Mix_GetError());
        return NULL;
    }
    return music;
}

// Function for initializing SDL
static int initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}

// Function for creating SDL window
static SDL_Window *createWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
{
    SDL_Window *window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return NULL;
    }
    return window;
}

// Function for opening audio with SDL_mixer
static int openAudio(int frequency, Uint16 format, int channels, int chunksize)
{
    if (Mix_OpenAudio(frequency, format, channels, chunksize) == -1)
    {
        fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
        return 1;
    }
    return 0;
}


// Function for creating SDL renderer
static SDL_Renderer *createRenderer(SDL_Window *window, int index, Uint32 flags)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, index, flags);
    if (renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return NULL;
    }
    return renderer;
}

// Function for loading an image to SDL_Texture
static SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL)
    {
        fprintf(stderr, "IMG_LoadTexture Error: %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}

// Function for handling events
static void handleEvents(int *quit, SDL_Event *event, SDL_Rect *box)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            *quit = 1;
        }
        else if (event->type == SDL_MOUSEBUTTONDOWN)
        {
            int mouseX = event->button.x;
            int mouseY = event->button.y;

            // Check which part of the box was clicked
            if (mouseX >= box->x && mouseX <= box->x + box->w / 2 &&
                mouseY >= box->y && mouseY <= box->y + box->h / 2)
            {
                printf("Clicked on top-left quadrant\n");
                fflush(stdout); // Flush the standard output buffer
                // TODO: Handle the click in the top-left quadrant
            }
            else if (mouseX >= box->x + box->w / 2 && mouseX <= box->x + box->w &&
                     mouseY >= box->y && mouseY <= box->y + box->h / 2)
            {
                printf("Clicked on top-right quadrant\n");
                fflush(stdout); // Flush the standard output buffer
                // TODO: Handle the click in the top-right quadrant
            }
            else if (mouseX >= box->x && mouseX <= box->x + box->w / 2 &&
                     mouseY >= box->y + box->h / 2 && mouseY <= box->y + box->h)
            {
                printf("Clicked on bottom-left  quadrant\n");
                fflush(stdout); // Flush the standard output buffer
                // TODO: Handle the click in the bottom-left quadrant
            }
            else if (mouseX >= box->x + box->w / 2 && mouseX <= box->x + box->w &&
                     mouseY >= box->y + box->h / 2 && mouseY <= box->y + box->h)
            {
                printf("Clicked on bottom-right quadrant\n");
                fflush(stdout); // Flush the standard output buffer
                // TODO: Handle the click in the bottom-right quadrant
            }
        }
    }
}

// Function for rendering the window
static void render(SDL_Renderer *renderer, SDL_Texture *backgroundImage, SDL_Rect *box, SDL_Rect *topLeft, SDL_Rect *topRight, SDL_Rect *bottomLeft, SDL_Rect *bottomRight)
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the Drake image above the box
    SDL_RenderCopy(renderer, backgroundImage, NULL, NULL);

    // Draw the box
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    SDL_RenderDrawRect(renderer, box);

    // Draw the quadrants
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    SDL_RenderFillRect(renderer, topLeft);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
    SDL_RenderFillRect(renderer, topRight);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
    SDL_RenderFillRect(renderer, bottomLeft);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color
    SDL_RenderFillRect(renderer, bottomRight);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    // Initialize SDL
    if (initSDL() != 0)
    {
        return 1;
    }

    // Create SDL window
    SDL_Window *window = createWindow("Play Space Song", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        SDL_Quit();
        return 1;
    }

    // Open audio with SDL_mixer
    if (openAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load music to Mix_Music
    Mix_Music *music = loadMusic("BeachHouseSpaceSong.flac");
    if (music == NULL)
    {
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Create SDL renderer
    SDL_Renderer *renderer = createRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        Mix_FreeMusic(music);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Load the image of Drake
    SDL_Texture *backgroundImage = loadImage(renderer, "beachHouse.jpg"); // Replace "drake_image.png" with the actual path to your image
    if (backgroundImage == NULL)
    {
        SDL_DestroyRenderer(renderer);
        Mix_FreeMusic(music);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Define box position and size
    SDL_Rect box = {100, 100, 600, 600};
    SDL_Rect topLeft = {box.x, box.y, box.w / 2, box.h / 2};
    SDL_Rect topRight = {box.x + box.w / 2, box.y, box.w / 2, box.h / 2};
    SDL_Rect bottomLeft = {box.x, box.y + box.h / 2, box.w / 2, box.h / 2};
    SDL_Rect bottomRight = {box.x + box.w / 2, box.y + box.h / 2, box.w / 2, box.h / 2};

    // Play music
    Mix_PlayMusic(music, -1);

    // Main loop
    int quit = 0;
    SDL_Event event;
    while (!quit)
    {
        handleEvents(&quit, &event, &box);
        render(renderer, backgroundImage, &box, &topLeft, &topRight, &bottomLeft, &bottomRight);
    }

    SDL_DestroyTexture(backgroundImage);
    Mix_FreeMusic(music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}