
#include "config.h"
#include "conway.h"

#include <SDL2/SDL.h>

void	update()
{


}

void	conway_swap_grids(t_conway *conway)
{
	t_conway_grid *swap;

	swap = conway->current_gen;
	conway->current_gen = conway->next_gen;
	conway->next_gen = swap;
}