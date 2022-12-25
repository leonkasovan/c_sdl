/*
 * SDL2 Test Input: keyboard joystick mouse
 */
#include <stdio.h>
#include <SDL.h>
#include <errno.h>
#define DEAD_ZONE 9999

void eventloop(FILE * outfile){
    while (1) {
		SDL_Event ev;

		if (SDL_PollEvent(&ev) == 0) {
			SDL_Delay(1);
			continue;
		}
		switch (ev.type) {
		case SDL_QUIT:
			fprintf(outfile, "Received SDL_QUIT - bye!\n");
			return;
		case SDL_JOYHATMOTION:
			fprintf(outfile, "hat[%d] value=%d\n", ev.jhat.hat, ev.jhat.value);
			break;
		case SDL_JOYAXISMOTION:
			if (ev.jaxis.axis == 0){
				if (ev.jaxis.value < -DEAD_ZONE){
					fprintf(outfile, "[LeftStick] Left axis[%d] value=%d\n", ev.jaxis.axis, ev.jaxis.value);
				}else if (ev.jaxis.value > DEAD_ZONE){
					fprintf(outfile, "[LeftStick] Right axis[%d] value=%d\n", ev.jaxis.axis, ev.jaxis.value);
				}
			}else if (ev.jaxis.axis == 1){
				if (ev.jaxis.value < -DEAD_ZONE){
					fprintf(outfile, "[LeftStick] Up axis[%d] value=%d\n", ev.jaxis.axis, ev.jaxis.value);
				}else if (ev.jaxis.value > DEAD_ZONE){
					fprintf(outfile, "[LeftStick] Down axis[%d] value=%d\n", ev.jaxis.axis, ev.jaxis.value);
				}
			}
			if (ev.jaxis.axis == 2){
				if (ev.jaxis.value < -DEAD_ZONE){
					fprintf(outfile, "[RightStick] Left axis[%d] value=%d\n", ev.jaxis.axis, ev.jaxis.value);
				}else if (ev.jaxis.value > DEAD_ZONE){
					fprintf(outfile, "[RightStick] Right axis[%d] value=%d\n", ev.jaxis.axis, ev.jaxis.value);
				}
			}else if (ev.jaxis.axis == 3){
				if (ev.jaxis.value < -DEAD_ZONE){
					fprintf(outfile, "[RightStick] Up axis[%d] value=%d\n", ev.jaxis.axis, ev.jaxis.value);
				}else if (ev.jaxis.value > DEAD_ZONE){
					fprintf(outfile, "[RightStick] Down axis[%d] value=%d\n", ev.jaxis.axis, ev.jaxis.value);
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			fprintf(outfile, "SDL_MOUSEBUTTONUP, button %d clicks %d\n",
				ev.button.button, (int) ev.button.clicks);
			break;
		case SDL_MOUSEBUTTONDOWN:
			fprintf(outfile, "SDL_MOUSEBUTTONDOWN, button %d clicks %d\n",ev.button.button, (int) ev.button.clicks);
			break;
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			if (ev.type == SDL_KEYUP)
				fprintf(outfile, "SDL_KEYUP: ");
			else
				fprintf(outfile, "SDL_KEYDOWN: ");
			
			fprintf(outfile, "Keycode: %s (%d) Scancode: %s (%d)\n",
				SDL_GetKeyName(ev.key.keysym.sym), ev.key.keysym.sym,
				SDL_GetScancodeName(ev.key.keysym.scancode),
				ev.key.keysym.scancode);
			
			if (ev.key.keysym.sym == SDLK_q) {
				fprintf(outfile, "You pressed Q - bye!\n");
				return;
			}
			break;
		case SDL_MOUSEWHEEL:
			fprintf(outfile, "MouseWheel: x: %d, y: %d\n", ev.wheel.x, ev.wheel.y);
			break;
		case SDL_TEXTINPUT:
			fprintf(outfile, "SDL_TEXTINPUT: %s\n", ev.text.text ? ev.text.text : "<NULL>");
			break;
		case SDL_JOYBUTTONDOWN:
			fprintf(outfile, "SDL_JOYBUTTONDOWN button %d state %d\n",(int) ev.jbutton.button,(int) ev.jbutton.state);
			break;
		case SDL_JOYBUTTONUP:
			fprintf(outfile, "SDL_JOYBUTTONUP button %d state %d\n",(int) ev.jbutton.button,(int) ev.jbutton.state);
			break;
		case SDL_MOUSEMOTION:
		case SDL_FINGERDOWN:
		case SDL_FINGERUP:
		case SDL_FINGERMOTION:
			break;
		case SDL_WINDOWEVENT:
			break;
		default:
			// fprintf(outfile, "SDL_Event of type: 0x%x received\n",
			// ev.type);
			break;
		}
    }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Joystick *gGameController = NULL;
    //SDL_Window *win = SDL_CreateWindow("Hello World!", 0, 0, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    //SDL_SetWindowTitle(win, "asdf");
    if (SDL_NumJoysticks() < 1) {
		printf("Warning: No joysticks connected!\n");
    } else {
		gGameController = SDL_JoystickOpen(0);
		if (gGameController == NULL) {
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
    }
#ifdef _WIN32
    // output debug prints to file on windows
    // const char* filename = "sdl2_test_out.txt";
    const char *filename = "-";
#else
    // output debug prints to stdout on other OS
    const char *filename = "-";
#endif
    FILE *output = NULL;

    if (argc > 1) {
		filename = argv[1];
    }
    if (strcmp(filename, "-") == 0)
		output = stdout;
    else
		output = fopen(filename, "w");
	
    if (!output) {
		fprintf(stderr, "Couldn't create debug output file!\n");
		exit(1);
    }
    eventloop(output);
    if (strcmp(filename, "-") != 0)
		fclose(output);
    SDL_JoystickClose(gGameController);
    gGameController = NULL;
    //SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
