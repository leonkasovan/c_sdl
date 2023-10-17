/*
Simple SDL 1.2 for RG35xx
using SDL_UpdateRect
*/
#include <SDL.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Surface* screen = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE);
    if (!screen) {
        fprintf(stderr, "SDL video mode set failed: %s\n", SDL_GetError());
        return 1;
    }

    // Set the drawing color to red
    Uint32 red = SDL_MapRGB(screen->format, 255, 0, 0);

    // Create a red rectangle
    SDL_Rect rect = { 0, 0, 200, 200 };
    SDL_FillRect(screen, &rect, red);
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    // Delay for a few seconds to see the window
    SDL_Delay(3000);

    // Cleanup and quit SDL
    SDL_Quit();

    return 0;
}
