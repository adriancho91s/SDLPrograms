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
static void handleEvents(int *quit, int *isPlaying, Mix_Music *music, SDL_Event *event, SDL_Rect *playButton, SDL_Rect *pauseButton, SDL_Rect *stopButton)
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

            // Check if the mouse click is inside one of the buttons
            if (mouseX >= playButton->x && mouseX <= playButton->x + playButton->w &&
                mouseY >= playButton->y && mouseY <= playButton->y + playButton->h)
            {
                if (!(*isPlaying))
                {
                    Mix_PlayMusic(music, 1);
                    *isPlaying = 1;
                }
            }
            else if (mouseX >= pauseButton->x && mouseX <= pauseButton->x + pauseButton->w &&
                     mouseY >= pauseButton->y && mouseY <= pauseButton->y + pauseButton->h)
            {
                if (*isPlaying)
                {
                    Mix_PauseMusic();
                    *isPlaying = 0;
                }
            }
            else if (mouseX >= stopButton->x && mouseX <= stopButton->x + stopButton->w &&
                     mouseY >= stopButton->y && mouseY <= stopButton->y + stopButton->h)
            {
                if (*isPlaying)
                {
                    Mix_HaltMusic();
                    *isPlaying = 0;
                }
            }
        }
    }
}

// Function for rendering the window
static void render(SDL_Renderer *renderer, SDL_Texture *drakeImage, SDL_Rect *playButton, SDL_Rect *pauseButton, SDL_Rect *stopButton)
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the Drake image above the buttons
    SDL_RenderCopy(renderer, drakeImage, NULL, NULL);

    // Draw buttons
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    SDL_RenderFillRect(renderer, playButton);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
    SDL_RenderFillRect(renderer, pauseButton);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
    SDL_RenderFillRect(renderer, stopButton);

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
    SDL_Window *window = createWindow("Play Space Song", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
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
    SDL_Texture *drakeImage = loadImage(renderer, "beachHouse.jpg"); // Replace "drake_image.png" with the actual path to your image
    if (drakeImage == NULL)
    {
        SDL_DestroyRenderer(renderer);
        Mix_FreeMusic(music);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Define button positions and sizes
    SDL_Rect playButton = {100, 200, 80, 40};
    SDL_Rect pauseButton = {200, 200, 80, 40};
    SDL_Rect stopButton = {300, 200, 80, 40};

    // Main loop
    int quit = 0;
    int isPlaying = 0;
    SDL_Event event;
    while (!quit)
    {
        handleEvents(&quit, &isPlaying, music, &event, &playButton, &pauseButton, &stopButton);
        render(renderer, drakeImage, &playButton, &pauseButton, &stopButton);
    }


    SDL_DestroyTexture(drakeImage);
    Mix_FreeMusic(music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}