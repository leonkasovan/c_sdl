/*
Simple SDL 1.2 for RG35xx
using SDL_CreateRGBSurface
*/
#include <SDL/SDL.h>
void putpixel(SDL_Surface* surface, int x, int y, Uint32 pixel);
int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window with hardware surface
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    if (!screen) {
        fprintf(stderr, "SDL video mode set failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create an RGB surface
    SDL_Surface* rgbSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0xFF0000, 0x000000, 0x000000, 0);
    // SDL_Surface* rgbSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 16, 0, 0, 0, 0);

    if (!rgbSurface) {
        fprintf(stderr, "SDL_CreateRGBSurface failed: %s\n", SDL_GetError());
        return 1;
    }

    // Draw a simple pattern on the RGB surface
    for (int y = 0; y < 240; y++) {
        for (int x = 0; x < 320; x++) {
            // Uint32 pixelColor = SDL_MapRGB(rgbSurface->format, (x+y) % 255, x % 255, y % 255);
            Uint32 pixelColor = SDL_MapRGB(rgbSurface->format, 255, 255, 255);
            putpixel(rgbSurface, x, y, pixelColor);
        }
    }

    // Blit the RGB surface onto the screen
    // SDL_Rect destRect = { 0, 0, 100, 100 };
    // SDL_BlitSurface(rgbSurface, NULL, screen, &destRect);
    SDL_BlitSurface(rgbSurface, NULL, screen, NULL);

    // Update the screen
    SDL_Flip(screen);

    // Wait for a few seconds
    SDL_Delay(3000);

    // Clean up and quit SDL
    SDL_FreeSurface(rgbSurface);
    SDL_Quit();

    return 0;
}

void putpixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16*)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xFF;
            p[1] = (pixel >> 8) & 0xFF;
            p[2] = pixel & 0xFF;
        } else {
            p[0] = pixel & 0xFF;
            p[1] = (pixel >> 8) & 0xFF;
            p[2] = (pixel >> 16) & 0xFF;
        }
        break;

    case 4:
        *(Uint32*)p = pixel;
        break;
    }
}
