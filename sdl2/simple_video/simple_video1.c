/*
Testing Simple Video for rg35xx using SDL2 Library
Result: 
    "INFO: Error: Unable to initialize SDL: No available video device"
*/
#include <SDL.h>

#define RG35_MENU_CODE      117             /* RG35xx button code */
#define RG35_UP_CODE        119             /* RG35xx button code */
#define RG35_RIGHT_CODE     100             /* RG35xx button code */
#define RG35_DOWN_CODE      115             /* RG35xx button code */
#define RG35_LEFT_CODE      113             /* RG35xx button code */
#define RG35_A_CODE          97             /* RG35xx button code */
#define RG35_B_CODE          98             /* RG35xx button code */
#define RG35_X_CODE         120             /* RG35xx button code */
#define RG35_Y_CODE         121             /* RG35xx button code */
#define RG35_SELECT_CODE    110             /* RG35xx button code */
#define RG35_START_CODE     109             /* RG35xx button code */
#define RG35_L1_CODE        104             /* RG35xx button code */
#define RG35_L2_CODE        106             /* RG35xx button code */
#define RG35_R1_CODE        108             /* RG35xx button code */
#define RG35_R2_CODE        107             /* RG35xx button code */

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error: Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL 2 Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Error: Unable to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Error: Unable to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set the drawing color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Clear the window
    SDL_RenderClear(renderer);

    // Create a red rectangle
    SDL_Rect rect = { 100, 100, 200, 200 };
    SDL_RenderFillRect(renderer, &rect);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Event loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == RG35_MENU_CODE){
                    quit = 1;
                }
            }
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
