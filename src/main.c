#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>

const float target_fps = (1 / 60.) * 1000;

int processEvents(SDL_Window *window)
{
	SDL_bool done = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT: {
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				printf("Close event");
				if (window) {
					SDL_DestroyWindow(window);
					window = NULL;
					done = 1;
				}
				break;
			}
		}
		case SDL_KEYDOWN: {
			printf("Key down %s\n",
			       SDL_GetKeyName(event.key.keysym.sym));
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: {
				done = 1;
				break;
			}
			}
		}
		}
	}
	return done;
}

void render(SDL_Renderer *renderer)
{
	// set screen to green
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	// set screen to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect = { 100, 100, 255, 255 };
	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);
}

void setDisplaySize(int x_offset, int y_offset, SDL_Window *window)
{
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	SDL_SetWindowSize(window, dm.w - x_offset, dm.h - y_offset);
}

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Test SDL2 in C", SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED, 0, 0,
				  SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	setDisplaySize(100, 200, window);

	int done = 0;
	while (!done) {
		// handle events
		done = processEvents(window);

		// render
		render(renderer);

		SDL_Delay(target_fps);
	}

	return 0;
}
