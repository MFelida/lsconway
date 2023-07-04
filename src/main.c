#include "config.h"
#include "display.h"
#include "conway.h"

#include <SDL2/SDL.h>
#include <stdio.h>

int main(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int game_running;

	game_running = initialize_window(window, renderer);
	while (game_running)
	{
		render(renderer);
		get_input(&game_running);
	}
	destroy_window(window, renderer);
	fprintf(stderr, "Reached end of main.\n");
}