/*
Simple SDL 1.2 for RG35xx
using SDL_Flip
*/
#include <SDL.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE);
    if (!screen) {
        fprintf(stderr, "SDL video mode set failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a red rectangle
    SDL_Rect rect = { 0, 0, 200, 200 };
    Uint32 green = SDL_MapRGB(screen->format, 0, 255, 0);
    SDL_FillRect(screen, &rect, green);

    // Update the screen using SDL_Flip (this swaps the back buffer with the front buffer)
    SDL_Flip(screen);

    // Delay for a few seconds to see the window
    SDL_Delay(3000);

    // Cleanup and quit SDL
    SDL_Quit();

    return 0;
}
