
#include "display.h"
#include "config.h"

#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window		*window;
SDL_Renderer	*renderer;

int	initialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return 0;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
			| SDL_WINDOW_INPUT_GRABBED);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL window.\n");
		return 0;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer.\n");
		return 0;
	}
	atexit(destroy_window);
	return 1;
}

void	destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void	get_input(int *game_running)
{
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		*game_running = 0;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			*game_running = 0;
		break;
	default:
		break;
	}
}

void	render(void)
{
	SDL_Rect	rect;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (int x = CELL_SIZE; x < WINDOW_WIDTH; x += CELL_SIZE)
	{
		rect.h = WINDOW_HEIGHT;
		rect.w = 1;
		rect.x = x - 1;
		rect.y = 0;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
		SDL_RenderFillRect(renderer, &rect);
	}
	SDL_RenderPresent(renderer);
}