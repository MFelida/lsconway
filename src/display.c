
#include "display.h"
#include "config.h"

#include <SDL2/SDL.h>
#include <stdio.h>

int	initialize_window(SDL_Window *window, SDL_Renderer *renderer)
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
		WINDOWS_HEIGHT,
		SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		fprintf(stderr, "Erro creating SDL window.\n");
		return 0;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer.\n");
		return 0;
	}
	return 1;
}

void	destroy_window(SDL_Window *window, SDL_Renderer *renderer)
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

void	render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}