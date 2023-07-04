#include "config.h"
#include "display.h"
#include "conway.h"

#include <SDL2/SDL.h>
#include <stdio.h>

int main(void)
{
	int	game_running;

	game_running = initialize_window();
	while (game_running)
	{
		render();
		get_input(&game_running);
	}
	fprintf(stderr, "End of main reached.\n");
}